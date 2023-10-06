add_executable(ledbutton
    parts/ultrasonic.c
    parts/button.c
    parts/led_control.c
    main.c
)

pico_enable_stdio_usb(ledbutton 1)
pico_enable_stdio_uart(ledbutton 0)

target_link_libraries(ledbutton pico_stdlib freertos)
pico_add_extra_outputs(ledbutton)
