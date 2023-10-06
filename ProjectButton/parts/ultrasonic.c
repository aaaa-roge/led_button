#include "ultrasonic.h"
#include "pico/stdlib.h"
#include <stdio.h>

void ultrasonic_init(int triggerPin, int echoPin) {
    printf("init ultrasonic\n");
    gpio_init(triggerPin);
    gpio_init(echoPin);
    gpio_set_dir(triggerPin, GPIO_OUT);
    gpio_set_dir(echoPin, GPIO_IN);
    printf("done init ultrasonic\n");
}


double get_distance(int triggerPin, int echoPin) {
    printf("checking distance\n");
    gpio_put(triggerPin, 0);
    sleep_us(2);
    gpio_put(triggerPin, 1);
    sleep_us(10);
    gpio_put(triggerPin, 0);

    // check echo pulse
    // wait for echo
    while(gpio_get(echoPin) == 0) {
    }

    long result = 0;
    // if 1, we got something
    while(gpio_get(echoPin) == 1) {
        result++;
    }
    printf("result = %d\n", result);
    return result;

}