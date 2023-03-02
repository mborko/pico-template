cmake_minimum_required(VERSION 3.12)

# Set the Board
set(PICO_BOARD pico_w)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-template C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.5.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.5.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

include(example_auto_set_url.cmake)

# Add blink example
add_subdirectory(blink)

# Add hello world examples
add_subdirectory(hello)

# Add ampel example
add_subdirectory(ampel)

# Add hardware examples
#add_subdirectory(mpu6050_i2c)
#add_subdirectory(mcp2515_can)

# Add MQTT Example
add_subdirectory(mqtt)

# Add FreeRTOS examples
#add_subdirectory(freertos)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )
