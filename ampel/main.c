#include "pico/stdlib.h"

#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x]))))) /* NOLINT(readability-misplaced-array-index) */

typedef void (*State_Function)(void);

void state_yellow_blinking(void);
void state_yellow(void);
void state_red(void);
void state_red_yellow(void);
void state_green(void);
void state_green_blinking(void);

typedef enum __attribute__((packed)) {
    STATE_YELLOW_BLINKING,
    STATE_YELLOW,
    STATE_RED,
    STATE_RED_YELLOW,
    STATE_GREEN,
    STATE_GREEN_BLINKING,

    STATE_MAX,
} State;

static State state;

static State_Function state_functions[STATE_MAX] = {
    [STATE_YELLOW_BLINKING] = state_yellow_blinking,
    [STATE_YELLOW]          = state_yellow,
    [STATE_RED]             = state_red,
    [STATE_RED_YELLOW]      = state_red_yellow,
    [STATE_GREEN]           = state_green,
    [STATE_GREEN_BLINKING]  = state_green_blinking,
};

typedef enum {
    LIGHT_RED,
    LIGHT_YELLOW,
    LIGHT_GREEN,
} Light;

static int pins[3] = {
    [LIGHT_RED]    = 0,
    [LIGHT_YELLOW] = 1,
    [LIGHT_GREEN]  = 2,
};

int main()
{
    for (int i = 0; i < COUNT_OF(pins); i++) {
        gpio_init(pins[i]);
        gpio_set_dir(pins[i], GPIO_OUT);
    }

    state = STATE_YELLOW_BLINKING;
    for (;;) {
        for (int i = 0; i < COUNT_OF(pins); i++) {
            gpio_put(pins[i], 0);
        }
        state_functions[state]();
    }
}

void state_yellow_blinking(void)
{
    for (int i = 0; i < 10; i++) {
        gpio_put(pins[LIGHT_YELLOW], 1);
        sleep_ms(500);
        gpio_put(pins[LIGHT_YELLOW], 0);
        sleep_ms(500);
    }

    state = STATE_RED;
}

void state_yellow(void)
{
    gpio_put(pins[LIGHT_YELLOW], 1);

    sleep_ms(4000);
    state = STATE_RED;
}

void state_red(void)
{
    gpio_put(pins[LIGHT_RED], 1);

    sleep_ms(5000);
    state = STATE_RED_YELLOW;
}

void state_red_yellow(void)
{
    gpio_put(pins[LIGHT_RED], 1);
    gpio_put(pins[LIGHT_YELLOW], 1);

    sleep_ms(4000);
    state = STATE_GREEN;
}

void state_green(void)
{
    gpio_put(pins[LIGHT_GREEN], 1);

    sleep_ms(5000);
    state = STATE_GREEN_BLINKING;
}

void state_green_blinking(void)
{
    for (int i = 0; i < 4; i++) {
        gpio_put(pins[LIGHT_GREEN], 0);
        sleep_ms(500);
        gpio_put(pins[LIGHT_GREEN], 1);
        sleep_ms(500);
    }

    state = STATE_YELLOW;
}

