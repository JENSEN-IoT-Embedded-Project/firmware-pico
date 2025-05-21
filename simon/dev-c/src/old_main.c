#include "pico/stdlib.h"
#include <stdio.h>
#include "pico_sensor.h"
#include "wifi_config.h"
#include "pico/cyw43_arch.h"
#include <string.h>
#include "lwip/apps/mqtt.h"
#include "lwip/ip_addr.h"

#define BTN 11
#define BUZZ 12
#define LED 13
#define TRIG 14
#define ECHO 15

void connect_to_wifi(){
//enabling dependencies
        cyw43_arch_init();
        cyw43_arch_enable_sta_mode();

        printf("Attempting to connect to wifi ...");

        if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
                printf("Failed to connect ..-");
        }
        else {
                printf("Connected to wifi: %s\n", WIFI_SSID);
        }
}


int main() {
  // init serial communication
  stdio_init_all();
  connect_to_wifi();

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

  wait(LED, BTN);

  // calibrates device after all pins initialized
  // and prints tolerance window
  uint32_t calibrated = pico_calibration(500, LED, BUZZ, TRIG, ECHO);
  uint32_t tolerance = calibrated * 0.3;
  printf("tolerance frame = %d - %d\n", (calibrated-tolerance), (calibrated+tolerance));

  // sets first value to calibrated value
  uint32_t lastValue = calibrated;

  // main loop
  while (true) {    
    uint distance = read_distance(TRIG, ECHO);

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
