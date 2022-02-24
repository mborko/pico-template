#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "GPIO.hpp"
#include <array>

#define nonBlockingDelay(x) \
  TickType_t currentTick = xTaskGetTickCount(); \
  while(xTaskGetTickCount() - currentTick < x)

#define WAIT 2000

static pico_cpp::GPIO_Pin ledPin(25,pico_cpp::PinType::Output);
TaskHandle_t xTaskOffHandle = NULL;
TaskHandle_t xTaskOnHandle = NULL;

void vTaskCodeOn( void * pvParameters )
{
  /* The parameter value is expected to be 1 as 1 is passed in the
     pvParameters value in the call to xTaskCreate() below. 
     configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
     */
  for( ;; )
  {
    printf("led-on\t");
    ledPin.set_high();

    nonBlockingDelay(WAIT);

    vTaskPrioritySet( xTaskOffHandle, uxTaskPriorityGet(NULL)+1 );
    printf("priorityOn: %i priorityOff: %i\r\n", int(uxTaskPriorityGet(xTaskOnHandle)), int(uxTaskPriorityGet(xTaskOffHandle)));
  }
}

void vTaskCodeOff( void * pvParameters )
{
  for( ;; )
  {
    printf("led-off\t");
    ledPin.set_low();

    nonBlockingDelay(WAIT);

    vTaskPrioritySet( xTaskOffHandle, uxTaskPriorityGet(NULL)-2 );
    printf("priorityOn: %i priorityOff: %i\r\n", int(uxTaskPriorityGet(xTaskOnHandle)), int(uxTaskPriorityGet(xTaskOffHandle)));
  }
}

int main() {
  stdio_init_all();

  xTaskCreate(
      vTaskCodeOn,  /* Function that implements the task. */
      "led-on",     /* Text name for the task. */
      1024,          /* Stack size in words, not bytes. */
      ( void * ) 1, /* Parameter passed into the task. */
      3,            /* Priority at which the task is created. */
      &xTaskOnHandle );   

  xTaskCreate(
      vTaskCodeOff, /* Function that implements the task. */
      "led-off",    /* Text name for the task. */
      1024,          /* Stack size in words, not bytes. */
      ( void * ) 1, /* Parameter passed into the task. */
      2,            /* Priority at which the task is created. */
      &xTaskOffHandle );   

  vTaskStartScheduler();
  while(1)
  {
    configASSERT(0);    /* We should never get here */
  }

}
