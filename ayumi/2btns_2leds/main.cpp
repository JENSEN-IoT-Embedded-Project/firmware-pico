#include "pico/stdlib.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    const uint LED_PIN1 = 16;
    const uint BUTTON_PIN1 = 17;

    const uint LED_PIN2 = 19;
    const uint BUTTON_PIN2 = 18;

    gpio_init(LED_PIN1);
    gpio_set_dir(LED_PIN1, GPIO_OUT);

    gpio_init(LED_PIN2);
    gpio_set_dir(LED_PIN2, GPIO_OUT);

    gpio_init(BUTTON_PIN1);
    gpio_set_dir(BUTTON_PIN1, GPIO_IN);
    gpio_pull_up(BUTTON_PIN1);

    gpio_init(BUTTON_PIN2);
    gpio_set_dir(BUTTON_PIN2, GPIO_IN);
    gpio_pull_up(BUTTON_PIN2);

    while (true) {
        if (gpio_get(BUTTON_PIN1) == 0) {
            gpio_put(LED_PIN1, 1);
            printf("high\n");
        } else {
            gpio_put(LED_PIN1, 0);
            printf("low\n");
        }
        sleep_ms(10);

        if (gpio_get(BUTTON_PIN2) == 0) {
            gpio_put(LED_PIN2, 1);
            printf("2 high\n");
        } else {
            gpio_put(LED_PIN2, 0);
            printf("2 low\n");
        sleep_ms(10);

        }
    }
    return 0;


} 

