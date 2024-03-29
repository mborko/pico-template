#include "hardware/structs/rosc.h"

#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"
#include "lwip/altcp_tcp.h"
#include "lwip/altcp_tls.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"

#include "tusb.h"

#include "wifi_config.h"

#define MQTT_TLS 0
#define LOCAL_IOT // LOCAL_IOT | AWS_IOT | MOSQUITTO_TEST
#include "mqtt_config.h"

#if MQTT_TLS
#ifdef CRYPTO_CERT
const char *cert = CRYPTO_CERT;
#endif
#ifdef CRYPTO_CA
const char *ca = CRYPTO_CA;
#endif
#ifdef CRYPTO_KEY
const char *key = CRYPTO_KEY;
#endif
#endif

typedef struct MQTT_CLIENT_T_ {
	ip_addr_t remote_addr;
	mqtt_client_t *mqtt_client;
	u8_t receiving;
	u32_t received;
	u32_t counter;
	u32_t reconnect;
} MQTT_CLIENT_T;

err_t mqtt_test_connect(MQTT_CLIENT_T *state);

/* cribbed from https://github.com/peterharperuk/pico-examples/tree/add_mbedtls_example */
/* Function to feed mbedtls entropy. May be better to move it to pico-sdk */
int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen) {
    /* Code borrowed from pico_lwip_random_byte(), which is static, so we cannot call it directly */
    static uint8_t byte;

    for(int p=0; p<len; p++) {
        for(int i=0;i<32;i++) {
            // picked a fairly arbitrary polynomial of 0x35u - this doesn't have to be crazily uniform.
            byte = ((byte << 1) | rosc_hw->randombit) ^ (byte & 0x80u ? 0x35u : 0);
            // delay a little because the random bit is a little slow
            busy_wait_at_least_cycles(30);
        }
        output[p] = byte;
    }

    *olen = len;
    return 0;
}

static MQTT_CLIENT_T* mqtt_client_init() {
    MQTT_CLIENT_T *state = new MQTT_CLIENT_T();
    if (!state) {
        printf("failed to allocate state\n");
        return nullptr;
    }
    state->receiving = 0;
    state->received = 0;
    return state;
}


void dns_found(const char *name, const ip_addr_t *ipaddr, void *callback_arg) {
    MQTT_CLIENT_T *state = static_cast<MQTT_CLIENT_T*>(callback_arg);
    printf("DNS query finished with resolved addr of %s.\n", ip4addr_ntoa(ipaddr));
    state->remote_addr = *ipaddr;
}


void run_dns_lookup(MQTT_CLIENT_T *state) {
    printf("Running DNS query for %s.\n", MQTT_SERVER_HOST);

    cyw43_arch_lwip_begin();
    err_t err = dns_gethostbyname(MQTT_SERVER_HOST, &(state->remote_addr), dns_found, state);
    cyw43_arch_lwip_end();

    if (err == ERR_ARG) {
        printf("failed to start DNS query\n");
        return;
    }

    if (err == ERR_OK) {
        printf("no lookup needed\n");
        return;
    }

    while (state->remote_addr.addr == 0) {
        cyw43_arch_poll();
        sleep_ms(1);
    }
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    MQTT_CLIENT_T *state = static_cast<MQTT_CLIENT_T *>(arg);
    if (status != 0) {
        printf("Error during connection: err %d.\n", status);
    } else {
        printf("MQTT connected.\n");
    }
}

void mqtt_pub_request_cb(void *arg, err_t err) {
    MQTT_CLIENT_T *state = static_cast<MQTT_CLIENT_T *>(arg);
    printf("mqtt_pub_request_cb: err %d\n", err);
    state->receiving = 0;
    state->received++;
}

err_t mqtt_test_publish(MQTT_CLIENT_T *state)
{
  char buffer[128];

  #if MQTT_TLS
  #define TLS_STR "TLS"
  #else
  #define TLS_STR ""
  #endif

  sprintf(buffer, "hello from picow %d / %d %s", state->received, state->counter, TLS_STR);

  err_t err;
  u8_t qos = 2; /* 0 1 or 2, see MQTT specification */
  u8_t retain = 0;
  cyw43_arch_lwip_begin();
  printf("MQTT PUBLISH\n");
  err = mqtt_publish(state->mqtt_client, "pico_w/test", buffer, strlen(buffer), qos, retain, mqtt_pub_request_cb, state);
  cyw43_arch_lwip_end();
  if(err != ERR_OK) {
    printf("Publish err: %d\n", err);
  }

  return err;
}

void mqtt_test_conn_config_cb(void *conn) {
    #if MQTT_TLS
    mbedtls_ssl_set_hostname(altcp_tls_context(static_cast<struct altcp_pcb *>(conn)), MQTT_SERVER_HOST);
    #endif
}


err_t mqtt_test_connect(MQTT_CLIENT_T *state) {
    printf("mqtt_test_connect inside\n");
    struct mqtt_connect_client_info_t ci;
    err_t err;

    memset(&ci, 0, sizeof(ci));

    ci.client_id = MQTT_CLIENT_ID;
    ci.client_user = MQTT_CLIENT_USER;
    ci.client_pass = MQTT_CLIENT_PW;
    ci.keep_alive = 60;
    ci.will_topic = MQTT_WILL_TOPIC;
    ci.will_msg = "Here we are!";
    ci.will_retain = 0;
    ci.will_qos = 0;

    #if MQTT_TLS

    struct altcp_tls_config *tls_config;
  
    #if defined(CRYPTO_CA) && defined(CRYPTO_KEY) && defined(CRYPTO_CERT)
    printf("Setting up TLS with 2wayauth.\n");
    tls_config = altcp_tls_create_config_client_2wayauth(
        (const u8_t *)ca, 1 + strlen((const char *)ca),
        (const u8_t *)key, 1 + strlen((const char *)key),
        (const u8_t *)"", 0,
        
        (const u8_t *)cert, 1 + strlen((const char *)cert)
    );
    #elif defined(CRYPTO_CERT)
    printf("Setting up TLS with cert.\n");
    tls_config = altcp_tls_create_config_client((const u8_t *) cert, 1 + strlen((const char *) cert));
    #endif

    if (tls_config == NULL) {
        printf("Failed to initialize config\n");
        return -1;
    }

    ci.tls_config = tls_config;
    #endif

    //err = mqtt_client_connect(state->mqtt_client, &(state->remote_addr), MQTT_SERVER_PORT, mqtt_connection_cb, state, &ci, mqtt_test_conn_config_cb);
    printf("mqtt_client_connect\n");
    err = mqtt_client_connect(state->mqtt_client, &(state->remote_addr), MQTT_SERVER_PORT, mqtt_connection_cb, state, &ci);

    if (err != ERR_OK) {
        printf("mqtt_connect return %d\n", err);
    }
    printf("ERR_OK");
    return err;
}

void mqtt_run_test(MQTT_CLIENT_T *state) {
    printf("mqtt_run_test\n");
    state->mqtt_client = mqtt_client_new();

    state->counter = 0;

    u32_t notReady = 5000;

    if (state->mqtt_client == NULL) {
        printf("Failed to create new mqtt client\n");
        return;
    }

    if (mqtt_test_connect(state) == ERR_OK) {
        while (true) {
            cyw43_arch_poll();
            sleep_ms(1);
            if (!notReady--) {
                if (mqtt_client_is_connected(state->mqtt_client)) {
                    cyw43_arch_lwip_begin();
                    state->receiving = 1;
                    
                    if (mqtt_test_publish(state) == ERR_OK) {
                        printf("published %d\n", state->counter);
                        state->counter++;
                    } // else ringbuffer is full and we need to wait for messages to flush.
                    cyw43_arch_lwip_end();
                } else {
                    printf("x");
                }

                // MEM_STATS_DISPLAY();
                // MEMP_STATS_DISPLAY(0);
                // MEMP_STATS_DISPLAY(1);

                notReady = 5000;
            }
        }
    }
}


void wait_for_usb() {
    while (!tud_cdc_connected()) {
        printf(".");
        sleep_ms(500);
    }
    printf("usb host detected\n");
}


int main() {
    stdio_init_all();

    wait_for_usb();

    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }
    cyw43_arch_enable_sta_mode();

    printf("Connecting to WiFi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to  connect.\n");
        return 1;
    } else {
        printf("Connected.\n");
    }

    MQTT_CLIENT_T *state = mqtt_client_init();
     
    run_dns_lookup(state);
 
    mqtt_run_test(state);

    cyw43_arch_deinit();
    return 0;
}
