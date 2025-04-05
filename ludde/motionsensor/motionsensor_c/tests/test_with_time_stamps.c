#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include <inttypes.h>


int main () {
	stdio_init_all();
	//declare 2 variables that will store 2 different time stamps
	absolute_time_t timer_start;
	absolute_time_t timer_end;
	//get time stamp for first variable
	timer_start = get_absolute_time();
	sleep_us(5000);
	//get time stamp for second variable
	timer_end = get_absolute_time();
    //return the diff in microseconds between the 2 time_stamps. and save in variable
	int64_t passed_us = absolute_time_diff_us(timer_start,timer_end);
	sleep_ms(5000);
    //should print something close very close to the microseconds constant in the first sleep_us function. 
	printf("microseconds passed: %lld\n",passed_us);
}
