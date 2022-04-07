add_executable(freertos_blink
  main.cpp 
  )

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(freertos_blink pico_stdlib)
pico_enable_stdio_usb(freertos_blink 1)
pico_enable_stdio_uart(freertos_blink 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(freertos_blink)

target_link_libraries(freertos_blink FreeRTOS pico-cpp)
