#include <stdio.h>
#include <string.h>

#include "lwip/err.h"
#include "lwip/apps/mqtt.h"

#include "mqtt_connect.h"
#include "config.h"

static mqtt_client_t *client = NULL;
volatile bool mqtt_is_connected = false;
volatile bool mqtt_connecting = false; 

void mqtt_pub_request_cb(void *arg, err_t result) {
    if (result == ERR_OK) {
        printf("Publish successful\n");
    } else {
        printf("Publish failed with error: %d\n", result);
    }
}


void mqtt_publish_message(const char *topic, const char *message) {
    err_t err = mqtt_publish(
        client,                      // Din globala mqtt_client_t*
        topic,                       // Topic-sträng
        message,                     // Payload
        strlen(message),             // Längd på meddelande
        0,                           // QoS 0
        0,                           // retain false
        mqtt_pub_request_cb,         // Callback
        NULL                         // Argument till callback (valfritt)
    );

    if (err != ERR_OK) {
        printf("Failed to start publish: %d\n", err);
    } else {
        printf("Publish initiated\n");
    }
}


void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("MQTT connected!\n");
        mqtt_is_connected = true;
    } else {
        printf("MQTT connection failed. Status: %d\n", status);
        mqtt_is_connected = false;
    }
    mqtt_connecting = false;  // Sätt flaggan till false när anslutningen är klar
}


bool connect_mqtt() {
    if (mqtt_connecting || mqtt_is_connected) {
        return false;  // Om anslutning pågår, gör inget nytt försök
    }

    ip_addr_t broker_ip;
    IP4_ADDR(&broker_ip, 192, 168, 0, 222);  // IP-adressen för MQTT-brokern

    printf("Attempting to allocate MQTT client...\n");

    if (client) {
        mqtt_disconnect(client);  // Säkerhetsåtgärd
        client = NULL;
    }

    client = mqtt_client_new();
    if (!client) {
        printf("Failed to allocate mqtt client\nCHECK MEMORY USAGE\n");
        return false;
    }

    struct mqtt_connect_client_info_t ci = {
        .client_id = DEVICE_ID,
        .client_user = NULL,
        .client_pass = NULL,
        .keep_alive = 60,
        .will_topic = NULL,
        .will_msg = NULL,
        .will_qos = 0,
        .will_retain = 0,
    };

    printf("Connecting to MQTT broker...\n");
    mqtt_connecting = true;  // Sätt flaggan till true när anslutning startar
    mqtt_client_connect(client, &broker_ip, 1883, mqtt_connection_cb, NULL, &ci);
    return true;
}
