#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/timer.h"
#include <inttypes.h>
#include <stdio.h>

int main() {
    stdio_init_all();
    const uint trigger = 15;
    const uint echo = 14;

    gpio_init(trigger);
    gpio_init(echo);
    gpio_set_dir(trigger,1);
    gpio_set_dir(echo,0);

    //start tid
    //sov
    //slut tid

    uint64_t time_passed = 0;
    double distance = 0;
    absolute_time_t time_start;
    absolute_time_t time_end;

    while(1) {
        gpio_put(trigger,1);
        sleep_us(10);
        gpio_put(trigger,0);

        while(!gpio_get(echo)) {
            tight_loop_contents();
        } 
        time_start = get_absolute_time();
        
        while(gpio_get(echo)) {
            //printf("Echo high\n");
            sleep_us(1);
        }


        time_end = get_absolute_time();
        
        time_passed = absolute_time_diff_us(time_start,time_end);
        distance = (time_passed * 0.0343)/2;

        printf("distance: %.4f in cm\n", distance);
        sleep_ms(1000);
    }
}

