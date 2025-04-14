#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/time.h"
#include "hardware/i2c.h"
#include "lcd.h"



#define SDA_PIN 4
#define SCL_PIN 5

int main () {
    stdio_init_all();

    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    lcd_init();

    lcd_send_commmand(0x80);
    //fortsätt läs på härifrån....


