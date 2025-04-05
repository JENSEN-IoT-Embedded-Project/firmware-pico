#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"


int main () {
	stdio_init_all();
	//declare 2 variables that will store 2 different time stamps
	absolute_time_t timer_start;
	absolute_time_t timer_end;
	//get time stamp for first variable
	timer_start = get_absolute_time();
	sleep_us(10000);
	//get time stamp for second variable
	timer_end = get_absolute_time();
    //genereate the diff in microseconds between the 2 time_stamps.
	int64_t passed_us = absolute_time_diff_us(timer_start,timer_end);

	sleep_ms(50000);

	printf("Time passed: %d",passed_us);
}
