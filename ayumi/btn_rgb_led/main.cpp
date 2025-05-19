#include "pico/stdlib.h"
#include <stdio.h>

//(left to right) RED_PIN, GND, GREEN_PIN, BLUE_PIN
const uint RED_PIN = 16;
const uint GREEN_PIN = 17;
const uint BLUE_PIN = 18;
const uint BUTTON_PIN = 19;

enum Color { OFF, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE };

void set_rgb(Color color) {
    gpio_put(RED_PIN, color == RED || color == YELLOW || color == MAGENTA || color == WHITE);
    gpio_put(GREEN_PIN, color == GREEN || color == YELLOW || color == CYAN || color == WHITE);
    gpio_put(BLUE_PIN, color == BLUE || color == MAGENTA || color == CYAN || color == WHITE);
}

int main() {
    stdio_init_all();

    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);

    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);

    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    Color color = OFF;

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0) {
            color = static_cast<Color>((color + 1) % 8);
            set_rgb(color);
            printf("Color: %d\n", color);
            while (gpio_get(BUTTON_PIN) == 0) {
                sleep_ms(10); // Debounce the button
            }
        }
        sleep_ms(100);
    }
}
