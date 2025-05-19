#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/ip_addr.h"
#include "wifi_config.h"
#include "lwip/dns.h"
#include <stdio.h>
#include "lwip/timeouts.h"
#include "mqtt_connect.h"
#include "pico_sensor.h"
#include "jsonify.h"
#include "buzzer_melodies.h"
#include "config.h"

#define BTN 11
#define BUZZ 12
#define LED 13
#define TRIG 14
#define ECHO 15

int main() {
    stdio_init_all();

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

    gpio_pwm_setup(BUZZ);
    gpio_pull_up(BTN);

    wait(LED, BTN);
    
    const int button = 11;

    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_up(button);
    	
    if (cyw43_arch_init()) {
        printf("WiFi init failed\n");
        return -1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to SSID: %s\n", WIFI_SSID);

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("WiFi connect failed\n");
        return -1;
    }

    printf("WiFi connected\n");
    printf("Main loop running... MQTT status: %d\n", mqtt_is_connected);


    // Vänta på att MQTT-anslutningen ska lyckas
    while (!mqtt_is_connected) {
        if (connect_mqtt()) {
            printf("MQTT connect initiated.\n");
        }

        for (int i = 0; i < 100; i++) {
            cyw43_arch_poll();
            sleep_ms(50);
            if (mqtt_is_connected || !mqtt_connecting) {
                break;
            }
        }  

        if (!mqtt_is_connected) {
            printf("MQTT not connected, retrying..\n");
            sleep_ms(2000);
        }
    }

    printf("Connected to MQTT :)\n");

    //_____________________________________________________


    // calibrates device after all pins initialized
    // and prints tolerance window
    uint32_t calibrated = pico_calibration(500, LED, BUZZ, TRIG, ECHO);
    uint32_t tolerance = 8;
    //uint32_t tolerance = calibrated * 0.3;
    printf("tolerance frame = %d - %d\n", (calibrated-tolerance), (calibrated+tolerance));

    uint lastDistance = calibrated;

    // main loop
    while (true) {    
        cyw43_arch_poll();
	    sys_check_timeouts();
        unsigned int distance = read_distance(TRIG, ECHO);

        printf("distance: %d cm\ncalibration: %dcm\n", distance, calibrated);

        // if distance is within tolerance frame
        if (distance > (calibrated - tolerance) && distance < (calibrated + tolerance)) {
        gpio_put(LED, 0);
        gpio_put(BUZZ, 0);
        } else {
        gpio_put(LED, 1);
        //gpio_put(BUZZ, 1);
        char* msg = create_json(DEVICE_ID, distance);
        mqtt_publish_message("sensors/simon-pico", msg);
        melody_careless_whisper(BUZZ);
        //sleep_ms(2000);
        }

        sleep_ms(80);
        lastDistance = distance;
    }
}