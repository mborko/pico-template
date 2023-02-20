set(SUB_PROJECT_NAME mqtt)

if (PICO_CYW43_SUPPORTED) # set by PICO_BOARD=pico_w
  if (NOT TARGET pico_cyw43_arch)
    message("Skipping Pico W MQTT example as support is not available")
  else()

    # Add executable. Default name is the project name, version 0.1
    add_executable(${SUB_PROJECT_NAME}
      # Library executables
      # src/mpu6050.cpp

      # Main executalbes
      src/picow_iot.cpp
    )

    # Add Include Directory
    target_include_directories(${SUB_PROJECT_NAME} PUBLIC include/)

    pico_enable_stdio_uart(${SUB_PROJECT_NAME} 0)
    pico_enable_stdio_usb(${SUB_PROJECT_NAME} 1)

    # Add any user requested libraries
    target_link_libraries(${SUB_PROJECT_NAME}
      pico_stdlib
      hardware_adc
      pico_cyw43_arch_lwip_threadsafe_background
      pico_lwip_mbedtls
      pico_mbedtls
      pico_lwip_mqtt
    )

    pico_add_extra_outputs(${SUB_PROJECT_NAME})
  endif()
endif()
