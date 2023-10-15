#ifndef ULTRA_H
#define ULTRA_H

#include <stdio.h>

void ultrasonic_init(int triggerPin, int echoPin);
double get_distance(int triggerPin, int echoPin);

#endif