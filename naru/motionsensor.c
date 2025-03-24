#include <stdio.h>
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>

void mosq() {
    int rc;
    struct mosquitto *mosq; // mosq library

    mosquitto_lib_init(); //to use mosq.h

    mosq = mosquitto_new("pico-w", true, NULL); // name, clean session true, false kom ihåg data, null (ingen custom data)
    if (!mosq) {
        printf("can't start mosq\n");
    }

    rc = mosquitto_connect(mosq, "192.168.1.231", 1883, 10);    // Connect to the broker (IP, port, keepalive)
    if (rc != MOSQ_ERR_SUCCESS) { // om returncode inte är (predefined success i mosq lib) så return typ av error code
        printf("can't connect, return code: %d\n", rc);
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
    }

    mosquitto_loop_start(mosq);

    // struct, message id(null = autoassign), topic, size in bytes, message, QoS(1 gång), om brokern ska komma ihåg(false for now) 
    rc = mosquitto_publish(mosq, NULL, "test", 17, "sensor triggered!", 1, false);
    if (rc != MOSQ_ERR_SUCCESS) {
        printf("failed to publish message, return code: %d\n", rc);
    }
    
    sleep(2);

}

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
    gpio_init(trigger);
    gpio_init(echo);
    gpio_set_dir(trigger, GPIO_OUT);
    gpio_set_dir(echo, GPIO_IN);

    while (true) {
        float distance = measureDistance();

        if (distance < 10) {
            mosq();
            sleep_us(1000);
        }
        sleep_ms(100);
    }

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}


