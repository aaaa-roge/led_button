#include "../headers/button.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <time.h>

#define MAX_BUTTONS 30

const int DEBOUNCE_DELAY = 50000;
// check last state of buttons
int last_button_state[MAX_BUTTONS];
// counter for how long pin was 1
int button_counter[MAX_BUTTONS];

// initialize button
void init_button(int buttonPin) {
    gpio_init(buttonPin);
    gpio_set_dir(buttonPin, GPIO_IN);
}

// debounce, so this returns true on button release, I can change it
int is_button_pressed(int buttonPin) {
    
    int pressed = gpio_get(buttonPin);
    // button state went from 0 to 1
    if(!last_button_state[buttonPin] && pressed) {
        last_button_state[buttonPin] = 1;
    } 
    // button state is still 1
    else if (last_button_state[buttonPin] && pressed) {
        button_counter[buttonPin]++;
        last_button_state[buttonPin] = 1;
    } 
    // button state 1 to 0, button released
    else if (last_button_state[buttonPin] && !pressed && button_counter[buttonPin] > DEBOUNCE_DELAY) {
        printf("%d %d\n", buttonPin, button_counter[buttonPin]);
        button_counter[buttonPin] = 0;
        last_button_state[buttonPin] = 0;
        return 1;
    }
    return 0;
}
