#include "pico_sensor.h"
#include "pico/stdlib.h"


// buzzes buzzer :)
void buzz(uint32_t time, int buzz_pin) { // time in ms (length of buzzing sound)
  gpio_put(buzz_pin, 1);
  sleep_ms(time);
  gpio_put(buzz_pin, 0);
}


// returns distance in cm
uint read_distance(int trig_pin, int echo_pin) {
  // variables for measuring time
  absolute_time_t start, end;
  uint32_t distance = 0;

    // send 10 ug signal
    gpio_put(trig_pin, 1);
    sleep_us(10);
    gpio_put(trig_pin, 0);

    // waits while echo pin get no signal
    while (gpio_get(echo_pin) == 0);
    start = get_absolute_time();

    // sets "end" to time when signal stops
    while (gpio_get(echo_pin) == 1);
    end = get_absolute_time();

    // calculates time from start - end
    uint64_t time = absolute_time_diff_us(start, end);
    // distance conversion to cm
    distance = time / 58;

  return distance;
}


// calibration reads value 10 times and returns the average
// bright led indicates calibration is ongoing
uint pico_calibration(uint32_t time, int led_pin, int buzz_pin, int trig_pin, int echo_pin) { //time in ms (time = time between calibration readings)
  uint32_t average = 0;
  //activate LED on pin 13
  gpio_put(led_pin, 1);

  // 10 times calculation
  for (int i = 0; i < 10; i++) {
    average += read_distance(trig_pin, echo_pin);
    sleep_ms(time);
    printf("average: %i\n", average);
  }
  // deactivate LED on pin 13
  gpio_put(led_pin, 0);

  //plays 2 quick sounds to indicate calibration is done
  buzz(100, buzz_pin);
  sleep_ms(100);
  buzz(100, buzz_pin);

  return average / 10;
}


void wait(int led_pin, int btn_pin) {
  // waits for button press
  while (gpio_get(btn_pin)) {
    gpio_put(led_pin, 1);
    sleep_ms(100);
    gpio_put(led_pin, 0);
    sleep_ms(100);
  }
}
