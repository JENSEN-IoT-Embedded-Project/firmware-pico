// written and tested in wokwi
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
  const uint TRIG = 14;
  const uint ECHO = 15;
  const uint LED = 13;

  // init serial communication
  stdio_init_all();
  
  gpio_init(LED);
  gpio_init(TRIG);
  gpio_init(ECHO);

  gpio_set_dir(LED, GPIO_OUT);
  gpio_set_dir(TRIG, GPIO_OUT);
  gpio_set_dir(ECHO, GPIO_IN);

  // variables for measuring time
  absolute_time_t start, end;
  uint distance = 0;

  // main loop
  while (true) {

    // send 10 ug signal
    gpio_put(TRIG, 1);
    sleep_us(10);
    gpio_put(TRIG, 0);

    // waits while echo pin get no signal
    while (gpio_get(ECHO) == 0);
    start = get_absolute_time();
    
    // sets "end" to time when signal stops 
    while (gpio_get(ECHO) == 1);
    end = get_absolute_time();

    // calculates time from start - end
    uint64_t time = absolute_time_diff_us(start, end);
    // distance conversion to cm
    distance = time / 58;
    
    printf("%d cm\n", distance);
    if (distance > 40) {
      gpio_put(LED, 1);
    } else {
      gpio_put(LED, 0);
    }

    sleep_ms(100);
  }

}
