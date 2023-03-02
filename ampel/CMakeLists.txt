add_executable(ampel
        main.c
        )

# pull in common dependencies
target_link_libraries(ampel pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(ampel)

# add url via pico_set_program_url
example_auto_set_url(ampel)
