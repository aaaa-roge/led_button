#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"
// #include "ButtonControl.h"

// LED array length, using define since it inits at compile time
#define LED_ARRAY_LENGTH 5


// initialize mutex, handle current pin
static SemaphoreHandle_t mutex;

/* declare LED pin numbers, this could technically be variable?
   decided not to so that we know where LEDs are wired up  
   LED_PINS will be in order from leftmost LED being at the start
   of the array and the rightmost LED being at the end */
const uint LED_PINS[LED_ARRAY_LENGTH] = {22, 21, 20, 19, 18};

// set bounds for moving the LED
const uint LEFT_BUTTON_PIN = 16;
const uint RIGHT_BUTTON_PIN = 17;

// initialize current pin to middle pin, I could hardcode this but decided against it
static int currentPinIndex = LED_ARRAY_LENGTH/2;

// button state so we can debounce
bool buttonOpen = false;

void led_task() {

    while(1) {

        if(gpio_get(LEFT_BUTTON_PIN) && currentPinIndex > 0 && buttonOpen) {

            buttonOpen = false;
            gpio_put(LED_PINS[currentPinIndex], 0);
            printf("L previous pin/index = %d / %d\n", currentPinIndex, LED_PINS[currentPinIndex]);
            // move to the left
            currentPinIndex--;
            printf("L new pin/index = %d / %d\n", currentPinIndex, LED_PINS[currentPinIndex]);
            gpio_put(LED_PINS[currentPinIndex], 1);

        }  else if(gpio_get(RIGHT_BUTTON_PIN) && currentPinIndex < LED_ARRAY_LENGTH-1 && buttonOpen) {

            buttonOpen = false;
            gpio_put(LED_PINS[currentPinIndex], 0);
            printf("R previous pin/index = %d / %d\n", currentPinIndex, LED_PINS[currentPinIndex]);
            // move to the right
            currentPinIndex++;
            printf("R new pin/index = %d / %d\n", currentPinIndex, LED_PINS[currentPinIndex]);
            gpio_put(LED_PINS[currentPinIndex], 1);

        } else if(!gpio_get(LEFT_BUTTON_PIN) && !gpio_get(RIGHT_BUTTON_PIN)) {

            buttonOpen = true;
            printf("current pin/index = %d / %d\n", currentPinIndex, LED_PINS[currentPinIndex]);
            
        }
    }
}


int main() {
    stdio_init_all();

    // initialize all LED pins
    for(int i=0; i<LED_ARRAY_LENGTH; i++) {
        gpio_init(LED_PINS[i]);
        gpio_set_dir(LED_PINS[i], GPIO_OUT);
    }

    // initialize buttons
    gpio_init(LEFT_BUTTON_PIN);
    gpio_set_dir(LEFT_BUTTON_PIN, GPIO_IN);
    gpio_init(RIGHT_BUTTON_PIN);
    gpio_set_dir(RIGHT_BUTTON_PIN, GPIO_IN);

    //create mutex before tasks
    mutex = xSemaphoreCreateMutex();

    // create button task
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);

    // light up the first LED
    gpio_put(LED_PINS[currentPinIndex], 1);

    // start task scheduler
    vTaskStartScheduler();

    while(1) {};

}