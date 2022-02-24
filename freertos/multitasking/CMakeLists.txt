add_executable(multitasking
        main.cpp
)

target_link_libraries(multitasking pico_stdlib pico_multicore FreeRTOS)

# enable USB output and disable UART output
pico_enable_stdio_usb(multitasking 1)
pico_enable_stdio_uart(multitasking 0)

pico_add_extra_outputs(multitasking)
