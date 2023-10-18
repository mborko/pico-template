add_executable(ampel-switch
        ampel-switch.c
        )

# pull in common dependencies
target_link_libraries(ampel-switch pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(ampel-switch)

# add url via pico_set_program_url
example_auto_set_url(ampel-switch)
