
#ifndef LED_CONTROL
#define LED_CONTROL

void led_array_init(uint *ledPins, int ledArrayLength, int startingPin);
void move_led(uint *ledPins, int direction);
int get_current_pin_index();

#endif