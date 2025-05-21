#ifndef MQTT_CONNECT_H
#define MQTT_CONNECT_H

#include <stdbool.h>
#include "lwip/err.h"
#include "lwip/apps/mqtt.h"

extern volatile bool mqtt_is_connected;
extern volatile bool mqtt_connecting;

void mqtt_pub_request_cb(void *arg, err_t result);
void mqtt_publish_message(const char *topic, const char *message);
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
bool connect_mqtt();

#endif  