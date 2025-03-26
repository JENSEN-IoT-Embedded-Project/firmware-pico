#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../include/alarm.h"

void play(void){

	float cmajor_frequencies[8] = {261.0f, 293.0f, 329.0f, 349.0f, 392.0f, 440.0f, 493.0f};


	// Activate PWM on pin 16
	gpio_set_function(16, GPIO_FUNC_PWM);

	//Slice connected to Pin 16, needed for effective usage of PWM
	uint slice_num = pwm_gpio_to_slice_num(16);

	//Set the period for the PWM-signal (wrap_value). PWM-timer will count up to given number.
	//Arg1 == Slice, Arg2 == Max value for timer (Starts at 0). Timer will go from 0 - 254 (255 steps) so given number will decide on how many of the steps the signal will be "HIGH".
	//Timer-cycle is decided by clockfrequency. High clockfrequency == shorter timer.
	pwm_set_wrap(slice_num, 255);

	//Arg1 == Slice, Arg2 == What channel in Slice to configure, Arg3 == How many of the steps the signal should be HIGH. Remmaining steps of cycle will be LOW
	//In this case, the duty cycle will be 25%, since cycle is 255 steps and high on first 128 steps. (2/4 == 50%)
	pwm_set_chan_level(slice_num, PWM_CHAN_A, 128);

	//Divides microcontrollers systemclock (125MHz for Pico W) with given frequency. The result will decide how fast PWM timer will be (PWM Frequnecy)
	//Enter number as float to avoid heltalsdivision :)
	pwm_set_clkdiv(slice_num, 125.0);

	while(1){
		for(int i = 0; i < 7; i++){
			float clkdiv = 125000000 / cmajor_frequencies[i];
			pwm_set_clkdiv(slice_num, clkdiv);
			pwm_set_enabled(slice_num, 1);
			sleep_ms(50);
		}
	}
}
