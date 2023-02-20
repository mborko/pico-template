#ifndef MQTT_CONFIG_H_
#define MQTT_CONFIG_H_

#define MQTT_CLIENT_ID "pico"
#define MQTT_CLIENT_USER "mqtt"
#define MQTT_CLIENT_PW ""
#define MQTT_WILL_TOPIC "TEST"

// Default Values
#ifdef LOCAL_IOT
#define MQTT_SERVER_HOST "192.168.0.1"
#define MQTT_SERVER_PORT 1883
#endif

// AWS IoT Core
#ifdef AWS_IOT
#define MQTT_SERVER_HOST "example.iot.us-east-1.amazonaws.com"
#define MQTT_SERVER_PORT 8883
#define CRYPTO_CERT \
"-----BEGIN CERTIFICATE-----\n" \
"-----END CERTIFICATE-----\n";
#define CRYPTO_KEY \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"-----END RSA PRIVATE KEY-----";
#define CRYPTO_CA \
"-----BEGIN CERTIFICATE-----\n" \
"-----END CERTIFICATE-----";
#endif

// Mosquitto test servers
#ifdef MOSQUITTO_TEST
#if MQTT_TLS
#define MQTT_SERVER_PORT 8883
#else
#define MQTT_SERVER_PORT 1883
#endif
#define MQTT_SERVER_HOST "test.mosquitto.org"
#define CRYPTO_CERT \
"-----BEGIN CERTIFICATE-----\n" \
"-----END CERTIFICATE-----\n"
#endif

#endif
