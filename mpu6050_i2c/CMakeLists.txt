add_executable(mpu6050_i2c
        mpu6050_i2c.c
        )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(mpu6050_i2c pico_stdlib hardware_i2c)

pico_enable_stdio_usb(mpu6050_i2c 1)


# create map/bin/hex file etc.
pico_add_extra_outputs(mpu6050_i2c)

# add url via pico_set_program_url
example_auto_set_url(mpu6050_i2c)
