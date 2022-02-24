#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <iostream>
#include "pico/stdlib.h"

TaskHandle_t tskHdnl_evGen          = nullptr;
TaskHandle_t tskHdnl_stateManager   = nullptr;
QueueHandle_t eventQueue            = nullptr;

const uint8_t EVENT_PIN_HIGH = 1;
const uint8_t EVENT_PIN_LOW  = 0;

void eventGenerator(void *p)
{
    const int pin = 15;
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    while (true) {
        gpio_put(pin, 1);
        xQueueSend(eventQueue, &EVENT_PIN_HIGH, 0);
        vTaskDelay( 200/portTICK_PERIOD_MS );
    
        gpio_put(pin, 0);
        xQueueSend(eventQueue, &EVENT_PIN_LOW, 0);
        vTaskDelay( 100/portTICK_PERIOD_MS );
    }
}

void stateManager(void *p)
{
    uint8_t i = 255;
    
    while(true)
    {
        if( xQueueReceive(eventQueue, &i, portMAX_DELAY) == pdPASS )
        {
            std::cout << "received " << i << std::endl;
            switch( i)
            {
                case EVENT_PIN_HIGH: std::cout << "Pin is high\n";
                                    break;
                case EVENT_PIN_LOW : std::cout << "Pin is low\n";
                                    break;
                default: std::cout << "Unkown state\n";
                                    break;
            }
        }
    }
}

int main()
{
    stdio_init_all();
    
    eventQueue = xQueueCreate(5, sizeof(uint8_t) );

    xTaskCreate(eventGenerator, "eventGenerator", 256, nullptr, 1, &tskHdnl_evGen);
    xTaskCreate(stateManager, "stateManager", 256, nullptr, 1, &tskHdnl_stateManager);

    vTaskStartScheduler();

    while (true)
    {
        // should only get here if there is insufficient RAM
    }
}
