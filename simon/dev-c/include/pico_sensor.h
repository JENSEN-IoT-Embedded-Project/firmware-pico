#pragma once

#include "pico/stdlib.h"

void buzz(uint32_t time, int buzz_pin);

unsigned int read_distance(int trig_pin, int echo_pin);

uint pico_calibration(uint32_t time, int led_pin, int buzz_pin, int trig_pin, int echo_pin);

void wait(int led_pin, int btn_pin);
