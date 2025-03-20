#include <stdio.h>
#include "pico/stdlib.h"

const uint trigger = 2;
const uint echo = 3;

float measureDistance() {
    gpio_put(trigger, 0);
    sleep_us(2);
    gpio_put(trigger, 1);
    sleep_us(10);
    gpio_put(trigger, 0);

    uint64_t startTime = 0, endTime = 0;
    while (gpio_get(echo) == 0) {
        startTime = time_us_64();
    }
    while (gpio_get(echo) == 1) {
        endTime = time_us_64();
    }

    uint64_t duration = endTime - startTime;
    float distance = (duration * 0.0343) / 2;
    return distance;
}

int main() {
    stdio_init_all();
    gpio_init(trigger);
    gpio_init(echo);
    gpio_set_dir(trigger, GPIO_OUT);
    gpio_set_dir(echo, GPIO_IN);

    printf("Distance measurement system active...\n");
    
    while (true) {
        float distance = measureDistance();
        printf("Distance: %.2f cm\n", distance);

        if (distance < 10) {
            printf("Intruder detected!\n");
        }
        sleep_ms(100);
    }
    return 0;
}
