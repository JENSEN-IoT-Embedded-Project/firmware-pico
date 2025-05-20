#include <stdio.h>
#include <string.h>

#include "lwip/err.h"
#include "lwip/apps/mqtt.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"

#include "mqtt_connect.h"
#include "config.h"

static mqtt_client_t *client = NULL;
volatile bool mqtt_is_connected = false;
volatile bool mqtt_connecting = false; 

static struct mqtt_connect_client_info_t ci = {
    .client_id = DEVICE_ID,
    .keep_alive = 60,
    .will_qos = 0,
};

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

static void dns_cb(const char *name, const ip_addr_t *ipaddr, void *arg) {
    if (ipaddr == NULL) {
        printf("DNS failed for %s\n", name);
        mqtt_connecting = false;
        return;
    }

    printf("Resolved %s to %s\n", name, ipaddr_ntoa(ipaddr));
    mqtt_client_connect(client, ipaddr, 1883, mqtt_connection_cb, NULL, &ci);
}

bool connect_mqtt() {
    if (mqtt_connecting || mqtt_is_connected) return false;

    if (client) {
        mqtt_disconnect(client);
        client = NULL;
    }

    client = mqtt_client_new();
    if (!client) {
        printf("Failed to allocate MQTT client\n");
        return false;
    }

    ip_addr_t resolved_ip;
    err_t err = dns_gethostbyname(MQTT_BROKER_ADDR, &resolved_ip, dns_cb, NULL);

    if (err == ERR_OK) {
        // Redan i cache – koppla direkt
        printf("DNS (cached): %s -> %s\n", MQTT_BROKER_ADDR, ipaddr_ntoa(&resolved_ip));
        mqtt_client_connect(client, &resolved_ip, 1883, mqtt_connection_cb, NULL, &ci);
    } else if (err == ERR_INPROGRESS) {
        // Callback kommer anropas när det är klart
        printf("DNS lookup started for %s\n", MQTT_BROKER_ADDR);
        mqtt_connecting = true;
    } else {
        printf("DNS error (%d)\n", err);
        return false;
    }

    return true;
}