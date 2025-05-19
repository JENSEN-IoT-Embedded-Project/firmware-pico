#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/ip_addr.h"
#include <stdio.h>

#ifndef SSID
#define SSID "default_ssid"
#endif

#ifndef PWD
#define PWD "default_pwd"
#endif

//#define CYW43_AUTH_WPA2_AES_PSK 0x00400004 //write what type of wpa you are using check pico-sdk lib for uint mask
                                           
#define MQTT_SERVER "172.20.10.13"
//#define MQTT_PORT 1883

void mqtt_connected_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("MQTT connect successful!\n");

        const char *topic = "sensor/motion";
        const char *payload = "motion detected";

        err_t pub_err = mqtt_publish(client, topic, payload, strlen(payload), 1, 0, NULL, NULL);
        if (pub_err == ERR_OK) {
            printf("Message published to topic '%s'\n", topic);
        } else {
            printf("Failed to publish message: %d\n", pub_err);
        }
    } else {
        printf("MQTT connection failed with status: %d\n", status);
    }
}


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
    sleep_ms(1000);


   
   //mqtt code here.
    mqtt_client_t *client = mqtt_client_new();
    if(!client) {
        printf("Failed to create MQTT client\n");
        return 1;
    }

    ip_addr_t broker_ip;
    if(!ip4addr_aton(MQTT_SERVER, &broker_ip)) {
        printf("Invalid IP address format: %s\n", MQTT_SERVER);
        return 1;
    }
    printf("Broker IP set, connection to %s...\n", MQTT_SERVER);
    struct mqtt_connect_client_info_t pico = {
        .client_id = "pico",
        .client_user = NULL,
        .client_pass = NULL,
        .keep_alive = 60,
        .will_topic = "pico/status",
        .will_msg = "offline",
        .will_qos = 1,
        .will_retain = 1,
    };

    sleep_ms(10000);

    mqtt_client_connect(client, &broker_ip, MQTT_PORT, mqtt_connected_cb, NULL, pico);

    while(1) {
        cyw43_arch_poll();
        sleep_ms(10);
    }
     
    return 0;
}
