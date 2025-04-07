#include "pico/stdlib.h"
#include <stdio.h>
int main() {
    stdio_init_all();
    const uint trigger = 15;
    const uint echo = 14;
    gpio_init(trigger);
    gpio_init(echo);
    gpio_set_dir(trigger,1);
    gpio_set_dir(echo,0);

    while(1) {
        gpio_put(trigger,1);
        sleep_us(10);
        gpio_put(trigger,0);
        sleep_us(2);

        if(gpio_get(echo)) {
            printf("Echo high\n");
        }
        else {
            printf("Echo low\n");
        }
    }
}

