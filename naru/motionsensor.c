#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>

#define WIFI_SSID "placeholder"
#define WIFI_PASS "placeholder"

// Wi-Fi connection setup
void wifi() {
    cyw43_arch_init();
    printf("Connecting to WiFi: %s\n", WIFI_SSID);
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect to WiFi!\n");
    } else {
        printf("Connected to WiFi!\n");
    }
}

// Ultrasonic distance sensor code
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
    wifi(); // Connect to Wi-Fi

    gpio_init(trigger);
    gpio_init(echo);
    gpio_set_dir(trigger, GPIO_OUT);
    gpio_set_dir(echo, GPIO_IN);

    while (true) {
        float distance = measureDistance();
        printf("Distance: %.2f cm\n", distance);

        if (distance < 10) { // If an object is detected within 10cm
            printf("Object detected, sending MQTT message!\n");
            sleep_ms(1000); // Delay to avoid multiple triggers
        }

        sleep_ms(100); // Small delay between measurements
    }

    return 0;
}
