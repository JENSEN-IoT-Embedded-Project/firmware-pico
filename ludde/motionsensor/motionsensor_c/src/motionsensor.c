#include "motionsensor.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/time.h"

//make sure to free memory when used
double* run_callibration(const uint gpio_out, const uint gpio_in,int size) {
    stdio_init_all();
    double* ref_values = (double*)malloc(size * sizeof(double));
    if(ref_values == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
    double distance = 0;
    uint64_t time_passed = 0;
    absolute_time_t time_start;
    absolute_time_t time_end;

    for(int i = 0; i < size; i++){
        printf("loop %d\n",i);
        sleep_ms(100);
        gpio_put(gpio_out,1);
        sleep_us(10);
        gpio_put(gpio_out,0);

        while(!gpio_get(gpio_in)) {
            tight_loop_contents();
        }
        time_start = get_absolute_time();
        
        while(gpio_get(gpio_in)) {
            sleep_us(1);
        }
        time_end = get_absolute_time();

        time_passed = absolute_time_diff_us(time_start,time_end);
        distance =(time_passed * 0.0343)/2.0;
        printf("%.2f\n",distance);
        ref_values[i] = distance;
        sleep_ms(1000);
    }
    return ref_values;
};

int calibration_quality_ok(double* arr, int size, int tolerance_value) {
    //bubble sort the array
    for(int i = 0 ; i < size -1 ; i++) {
        for(int j = 0; j < size-1; j++) {
            if(arr[j] > arr[j+1]) {
                double temp = arr[j]; 
                arr[j] = arr[j + 1];
                arr[j + 1] = temp; 
            }
        }
    }
    if((arr[size-1] - arr[0]) > tolerance_value) {
        return 0;
    }
    return 1;
};

void set_reference_level(double *value,double arr[],int size) { 
    double reference_level = 0;
    for(int i = 0; i < size; i++) {
        reference_level += arr[i];
    }
    *value = reference_level/size;
};

    
int motion_scan(const uint gpio_out,const uint gpio_in,double reference_level,double tolerance_level) {
    double distance = 0;
    uint64_t time_passed = 0;
    absolute_time_t time_start;
    absolute_time_t time_end;
    while(1) {
        gpio_put(gpio_out,1);
        sleep_ms(10);
        gpio_put(gpio_out,0);

        while(!gpio_get(gpio_in)){
            tight_loop_contents();
        }
        time_start = get_absolute_time();

        while(gpio_get(gpio_in)) {
            sleep_us(1);
        }
        time_end = get_absolute_time();

        time_passed = absolute_time_diff_us(time_start,time_end);
        distance = (time_passed * 0.0343)/2;
        printf("%.2f\n",distance);
        sleep_ms(100);
        if(distance >= (reference_level + tolerance_level) || distance <=(reference_level - tolerance_level)) {
            return 0;
        }
    }

};





