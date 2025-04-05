#include "pico/stdlib.h"
#include "stdio.h"
#define TRIGG 15
#define ECHO 14
double sonic_sensor(uint *trigger_pin, uint *echo_pin);
int main() {
	stdio_init_all();
    //initialize gpio for trigger and echo pins and set directon
	gpio_init(TRIGG);
	gpio_init(ECHO);
	gpio_set_dir(TRIGG,1);
	gpio_set_dir(ECHO,0);
	double distance = 0;

	while(1) {
		distance = sonic_sensor(TRIGG,ECHO);
		printf("%d",distance);
	}
	
}

double sonic_sensor(uint *trigger_pin, uint *echo_pin) {
	double distance = 0;
	//send out and turn off signal to trigger pin.
	gpio_put(trigger_pin,0);
	sleep_ms(10);
	gpio_put(trigger_pin,1);
	sleep_ms(10);
	gpio_put(trigger_pin,0);
	sleep_ms(2);
	int time_low = 0; 
	int time_high = 0;
	absolute_time_t timer_start;
	absolute_time_t timer_end;
	while(gpio_get(echo_pin) == 0){
		timer_start = get_absolute_time();
	}
	time_end = get_absolute_time();

	while(gpio_get(echo_pin) == 1) {
	}
	tick_stop(time_high);

	time_passed = time_low - time_high;

	distance = time_passed algoritm för ljudets hastighet / 2 




	


	return distance;

}
