#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include "wifi_config.h"
#include "hardware/i2c.h"
#include "lcd.h"
#include "func.h"

// Ultrasonic distance sensor code
const uint buzzer = 14;
const uint trigger = 2;
const uint echo = 3;
const uint SDA_PIN = 4;
const uint SCL_PIN = 5;

void wifi() {
    cyw43_arch_init(); // unsure if this works only with pico_cyw43_arch_none, but since i couldnt build with this cant check
    cyw43_arch_enable_sta_mode(); // this is ONLY used with pico_cyw43_arch_lwip_threadsafe_background
    printf("Connecting to WiFi: %s\n", WIFI_SSID);
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect to WiFi!\n");
    } else {
        printf("Connected to WiFi!\n");
    }
}

int main() {
	sleep_ms(1000);
    stdio_init_all();
    wifi(); // Connect to Wi-Fi
    
    gpio_init(trigger);
    gpio_set_dir(trigger, GPIO_OUT);
    
    gpio_init(echo);
    gpio_set_dir(echo, GPIO_IN);
    
    gpio_init(buzzer);
    gpio_set_dir(buzzer, GPIO_OUT);
    
    // Initialize I2C0 at 100kHz on default SDA and SCL pins for the Pico
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
	lcd_init();
    
    while (true) {
    	float distance = measureDistance();
    	
		char buffer[16];
		snprintf(buffer, sizeof(buffer), "%.2f cm", distance);
		
		lcd_search(buffer);

        if (distance < 10) { // If an object is detected within 10cm
        buzz(500);
   		lcd_alarm(buffer);
            sleep_ms(5000); // Delay to avoid multiple triggers
        }

        sleep_ms(100); // Small delay between measurements
    }

    return 0;
}
