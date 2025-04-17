#include "pico/stdlib.h"
#include <stdio.h>

#define BTN 11
#define BUZZ 12
#define LED 13
#define TRIG 14
#define ECHO 15

// buzzes buzzer :)
void buzz(uint32_t time) { // time in ms
  gpio_put(BUZZ, 1);
  sleep_ms(time);
  gpio_put(BUZZ, 0);
}

// returns distance in cm
int read_distance() {
  // variables for measuring time
  absolute_time_t start, end;
  uint32_t distance = 0;

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

  return distance;
}

// calibration reads value 10 times and returns the average
// bright led indicates calibration is ongoing
int pico_calibration(uint32_t time) { //time in ms
  uint32_t average = 0;
  //activate LED on pin 13
  gpio_put(LED, 1);

  // 10 times calculation
  for (int i = 0; i < 10; i++) {
    average += read_distance();
    sleep_ms(time);
    printf("average: %i\n", average);
  }
  // deactivate LED on pin 13
  gpio_put(LED, 0);
  
  //plays 2 quick sounds to indicate calibration is done
  buzz(100);
  sleep_ms(100);
  buzz(100);

  return average / 10;
}

void wait() {
  // waits for button press
  while (gpio_get(BTN)) {
    gpio_put(LED, 1);
    sleep_ms(100);
    gpio_put(LED, 0);
    sleep_ms(100);
  }
}


int main() {
  // init serial communication
  stdio_init_all();

  //const uint TRIG = 14;
  //const uint ECHO = 15;
  //const uint LED = 13;
  
  gpio_init(LED);
  gpio_init(TRIG);
  gpio_init(ECHO);
  gpio_init(BUZZ);
  gpio_init(BTN);

  gpio_set_dir(LED, GPIO_OUT);
  gpio_set_dir(TRIG, GPIO_OUT);
  gpio_set_dir(ECHO, GPIO_IN);
  gpio_set_dir(BUZZ, GPIO_OUT);
  gpio_set_dir(BTN, GPIO_IN);

  gpio_pull_up(BTN);

  wait();

  // calibrates device after all pins initialized
  // and prints tolerance window
  uint32_t calibrated = pico_calibration(500);
  uint32_t tolerance = calibrated * 0.3;
  printf("tolerance frame = %d - %d\n", (calibrated-tolerance), (calibrated+tolerance));

  // sets first value to calibrated value
  uint32_t lastValue = calibrated;

  // main loop
  while (true) {    
    uint distance = read_distance();

    printf("distance: %d cm\ncalibration: %dcm\nlastValue: %d\n", distance, calibrated, lastValue);

    // if distance is within tolerance frame
    if ((calibrated - tolerance) < (distance + lastValue) / 2 && (calibrated + tolerance) > (distance + lastValue) / 2) {
      gpio_put(LED, 0);
      gpio_put(BUZZ, 0);
    } else {
      gpio_put(LED, 1);
      gpio_put(BUZZ, 1);
    }

    lastValue = distance;

    sleep_ms(80);
  }
}
