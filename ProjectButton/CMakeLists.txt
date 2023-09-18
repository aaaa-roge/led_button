add_executable(ledbutton
    main.c
)

pico_enable_stdio_usb(ledbutton 1)
pico_enable_stdio_uart(ledbutton 0)

target_link_libraries(ledbutton pico_stdlib freertos)
pico_add_extra_outputs(ledbutton)
