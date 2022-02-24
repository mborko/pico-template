set(FREERTOS_SOURCE ./FreeRTOS-Kernel)

add_library(
  FreeRTOS STATIC ${FREERTOS_SOURCE}/croutine.c
  ${FREERTOS_SOURCE}/event_groups.c
  ${FREERTOS_SOURCE}/list.c
  ${FREERTOS_SOURCE}/queue.c
  ${FREERTOS_SOURCE}/stream_buffer.c
  ${FREERTOS_SOURCE}/tasks.c
  ${FREERTOS_SOURCE}/timers.c
  ${FREERTOS_SOURCE}/portable/GCC/ARM_CM0/port.c
  ${FREERTOS_SOURCE}/portable/MemMang/heap_4.c
  ./support/IdleMemory.c
)

target_include_directories(
  FreeRTOS PUBLIC ${FREERTOS_SOURCE}/include 
  ./include
  ${FREERTOS_SOURCE}/portable/GCC/ARM_CM0
)

