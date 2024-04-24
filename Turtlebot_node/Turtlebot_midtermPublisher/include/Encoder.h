#ifndef _Encoder_H_
#define _Encoder_H_

#include <Arduino.h>

// Define the pulses per revolution (PPR) constant
#define PPR 441.0

void Encoder_init();

void Encoder_check();

#endif