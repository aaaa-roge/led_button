#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"
#include "parts/led_control.h"
// #include "ButtonControl.h"

// LED array length, using define since it inits at compile time
#define LED_ARRAY_LENGTH 5

/* declare LED pin numbers, this could technically be variable?
   decided not to so that we know where LEDs are wired up  
   LED_PINS will be in order from leftmost LED being at the start
   of the array and the rightmost LED being at the end */
uint LED_PINS[LED_ARRAY_LENGTH] = {22, 21, 20, 19, 18};

// set bounds for moving the LED
const uint LEFT_BUTTON_PIN = 16;
const uint RIGHT_BUTTON_PIN = 17;

// button state so we can debounce
bool buttonOpen = false;


void controller_task() {
    while(1) {

        if(is_button_pressed(LEFT_BUTTON_PIN) ) {
            move_led(LED_PINS, -1);
        }  else if(is_button_pressed(RIGHT_BUTTON_PIN) ) {
            move_led(LED_PINS, 1);

        }
    }
}

int main() {
    stdio_init_all();

    led_array_init(LED_PINS, LED_ARRAY_LENGTH, LED_ARRAY_LENGTH/2);

    // initialize buttons
    init_button(LEFT_BUTTON_PIN);
    init_button(RIGHT_BUTTON_PIN);

    // create button task
    xTaskCreate(controller_task, "controller_task", 256, NULL, 1, NULL);

    // start task scheduler
    vTaskStartScheduler();

    while(1) {};

}