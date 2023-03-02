#include "pico/stdlib.h"

typedef enum __attribute__((packed)) {
    YELLOW_BLINK,
    RED,
    RED_YELLOW,
    GRUEN,
    GRUEN_BLINK,
    YELLOW
} AmpelStates;

static const uint RED_LED_PIN = 0;
static const uint YELLOW_LED_PIN = 1;
static const uint GREEN_LED_PIN = 2;

static AmpelStates current_state = YELLOW_BLINK;

int main() {
    gpio_init(RED_LED_PIN);
    gpio_init(YELLOW_LED_PIN);
    gpio_init(GREEN_LED_PIN);

    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    while (true) {
        switch (current_state) {
            case YELLOW_BLINK:
                gpio_put(RED_LED_PIN, 0);
                gpio_put(YELLOW_LED_PIN, 0);
                gpio_put(GREEN_LED_PIN, 0);

                for (uint8_t i = 0; i < 10; i++) {
                    gpio_put(YELLOW_LED_PIN, 0);
                    sleep_ms(500);
                    gpio_put(YELLOW_LED_PIN, 1);
                    sleep_ms(500);
                }

                current_state = RED;

                break;
            case RED:
                gpio_put(RED_LED_PIN, 0);
                gpio_put(YELLOW_LED_PIN, 0);
                gpio_put(GREEN_LED_PIN, 0);

                gpio_put(RED_LED_PIN, 1);

                sleep_ms(4000);

                current_state = RED_YELLOW;

                break;
            case RED_YELLOW:
                gpio_put(RED_LED_PIN, 0);
                gpio_put(YELLOW_LED_PIN, 0);
                gpio_put(GREEN_LED_PIN, 0);

                gpio_put(RED_LED_PIN, 1);
                gpio_put(YELLOW_LED_PIN, 1);

                sleep_ms(4000);

                current_state = GRUEN;

                break;
            case GRUEN:
                gpio_put(RED_LED_PIN, 0);
                gpio_put(RED_LED_PIN, 0);
                gpio_put(YELLOW_LED_PIN, 0);

                gpio_put(GREEN_LED_PIN, 1);

                sleep_ms(4000);

                current_state = GRUEN_BLINK;

                break;
            case GRUEN_BLINK:
                gpio_put(RED_LED_PIN, 0);
                gpio_put(RED_LED_PIN, 0);
                gpio_put(YELLOW_LED_PIN, 0);

                for (uint8_t i = 0; i < 4; i++) {
                    gpio_put(GREEN_LED_PIN, 0);
                    sleep_ms(500);
                    gpio_put(GREEN_LED_PIN, 1);
                    sleep_ms(500);
                }

                current_state = YELLOW;

                break;
            case YELLOW:
                gpio_put(RED_LED_PIN, 0);
                gpio_put(RED_LED_PIN, 0);
                gpio_put(YELLOW_LED_PIN, 0);

                gpio_put(YELLOW_LED_PIN, 1);

                sleep_ms(4000);

                current_state = RED;

                break;
        }
    }
}
