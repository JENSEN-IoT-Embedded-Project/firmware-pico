#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lcd.h"
#include "pico/time.h"


#define SDA_PIN 4
#define SCL_PIN 5
#define TRIGG_PIN 15
#define ECHO_PIN 14

int main () {
    stdio_init_all();

    //lcd screen setup
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    lcd_init();
    //ultrasonic setup
    gpio_init(TRIGG_PIN);
    gpio_init(ECHO_PIN);
    gpio_set_dir(TRIGG_PIN, 1);
    gpio_set_dir(ECHO_PIN, 0);

    // variables for 
    absolute_time_t time_start = 0;
    absolute_time_t time_end = 0;
    int64_t time_diff = 0;
    double distance = 0;
    
    while (1) {
        char str[100];
        gpio_put(TRIGG_PIN, 1);
        sleep_us(10);
        gpio_put(TRIGG_PIN, 0);

        while(!gpio_get(ECHO_PIN)) {
            tight_loop_contents();
        }
        time_start = get_absolute_time();

        while(gpio_get(ECHO_PIN)) {
            sleep_us(1);
        }
        time_end = get_absolute_time();

        time_diff = absolute_time_diff_us(time_start,time_end);
        
        distance = (time_diff * 0.0343)/2;
        printf("Distance: %.2f\n",distance);
        sprintf(str,"Distance: %.2f",distance);
        //lcd_print takes an const char as argument but
        //need to convert distance.
        lcd_send_command(LCD_RETURNHOME);
        lcd_clear();
        lcd_print(str);
        sleep_ms(1000);

    }
}

