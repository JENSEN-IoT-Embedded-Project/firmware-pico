#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include "pico/stdlib.h"
double* run_callibration(const uint pin1, const uint pin2,int size);
int calibration_quality_ok(double* arr, int size, int tolerance_value);
void set_reference_level(double *value,double arr[],int size);
#endif


    


