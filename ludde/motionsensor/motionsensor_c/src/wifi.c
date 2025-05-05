#include "wifi.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>


int connect_to_wifi(const char *ssid,const char *pwd) {
    if(cyw43_arch_init()) {
        fprintf(stderr,"Error: cyw43_arch_init failed\n");
        return 0;
    }
    printf("cyw43_arch initialized\n");
    cyw43_arch_enable_sta_mode();

    if(cyw43_arch_wifi_connect_timeout_ms(SSID,PWD,CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        fprintf(stderr, "ERROR: unable to conect to wifi\n");
        return 0;
    }
    printf("Connected to wifi: %s\n",SSID);
    return 1;
};

