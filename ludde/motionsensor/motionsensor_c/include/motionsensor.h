#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include "pico/stdlib.h"
double* run_callibration(const uint gpio_out, const uint gpio_in,int size);
int calibration_quality_ok(double* arr, int size, int tolerance_value);
void set_reference_level(double *value,double arr[],int size);
int motion_scan(const uint gpio_out, const uint gpio_in, double reference_level , double tolerance_level);
#endif


    


