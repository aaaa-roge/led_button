
#include "pico/stdlib.h"
#include <stdio.h>

int current_pin_index = 0;
int led_array_length = 0;

// LED init
void led_array_init(uint *ledPins, int ledArrayLength, int startingPin) {

   // set vars
   led_array_length = ledArrayLength;
   current_pin_index = startingPin;

   // initialize all LED pins
    for(int i=0; i<led_array_length; i++) {
        gpio_init(ledPins[i]);
        gpio_set_dir(ledPins[i], GPIO_OUT);
    }

   // initialize current pin
   gpio_put(ledPins[current_pin_index], 1);
}


/*
ledPins - led pin array
direction - -1/left, 1/right
*/
void move_led(uint *ledPins, int direction) {
   
   gpio_put(ledPins[current_pin_index], 0);

   if(direction == 1 && current_pin_index < led_array_length-1) {
      printf("L previous pin/index = %d / %d\n", current_pin_index, ledPins[current_pin_index]);
      current_pin_index++;
      printf("L new pin/index = %d / %d\n", current_pin_index, ledPins[current_pin_index]);
   } else if (direction == -1 && current_pin_index > 0) {
      printf("R previous pin/index = %d / %d\n", current_pin_index, ledPins[current_pin_index]);
      current_pin_index--;
      printf("R new pin/index = %d / %d\n", current_pin_index, ledPins[current_pin_index]);
   }

   gpio_put(ledPins[current_pin_index], 1);
   
}


int get_current_pin_index() {
   return current_pin_index;
}