#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#define SSID "writeyours"
#define PWD  "write yours"
#define CYW43_AUTH_WPA2_AES_PSK 0x00400004 //write what type of wpa you are using check pico-sdk lib for uint mask
int main() {
    stdio_init_all();
    sleep_ms(3000);

    //activate cyw43 architecture to be able to controll the onboard drivers on the pico like the wifi chip 
    if (cyw43_arch_init()) {
        fprintf(stderr,"ERROR: cyw43_arch_init failed\n");
        return 1;
    }
    printf("cyw43_arch initialized\n");
    //activate the wifi chip as a client to connect to your wifi 
    cyw43_arch_enable_sta_mode();
    //Connect to listed wifi.
    if(cyw43_arch_wifi_connect_timeout_ms(SSID,PWD,CYW43_AUTH_WPA2_AES_PSK,30000)) {
        fprintf(stderr,"ERROR: unable to connect to wifi\n");
        return 1;
    }
    printf("Connected to wifi: %s\n",SSID);
    while(1) {
        sleep_ms(100);
    }
    return 0;
}
