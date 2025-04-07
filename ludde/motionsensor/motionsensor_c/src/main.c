#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include <inttypes.h>
double sonic_sensor(const uint trigger_pin,const uint echo_pin);
int main() {
	stdio_init_all();
    //initialize gpio for trigger and echo pins and set directon
    const uint TRIGG = 15;
    const uint ECHO = 14;
	gpio_init(TRIGG);
	gpio_init(ECHO);
	gpio_set_dir(TRIGG,1);
	gpio_set_dir(ECHO,0);
	double distance = 0;

	while(1) {
		distance = sonic_sensor(TRIGG,ECHO);
	}
    return 0;
}
double sonic_sensor(const uint trigger_pin,const uint echo_pin) {
	double distance = 1;
    //send out singal to trigger pin
    gpio_put(trigger_pin, 0);
    sleep_us(2);
	gpio_put(trigger_pin,1);
	sleep_us(10);
    gpio_put(trigger_pin,0);
	absolute_time_t time_start;
	absolute_time_t time_end;
    int64_t us_low = 0;
    int64_t us_high = 0;
    //count and return time while echo pin is not reciving data
	while(gpio_get(echo_pin) == 0){
        printf("Echo pin off\n");
		time_start = get_absolute_time();
	} 
	time_end = get_absolute_time();
    us_low = absolute_time_diff_us(time_start,time_end);   
    printf("microseconds low: %lld\n",us_low);
	while(gpio_get(echo_pin) == 1) {
       printf("Echo pin on\n");
       time_start = get_absolute_time(); 
	}
    time_end = get_absolute_time();
    us_high = absolute_time_diff_us(time_start,time_end);
    printf("microseconds high: %lld\n", us_high);


	return distance;

}
