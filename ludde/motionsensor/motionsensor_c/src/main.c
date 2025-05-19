#include "motionsensor.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/cyw43_arch.h"
#include "wifi.h"
#include "lwip/apps/mqtt.h"
#include "lwip/ip_addr.h"
#include "mqtt.h"

#ifndef SSID
#define SSID "default_ssid"
#endif

#ifndef PWD
#define PWD "default_pwd"
#endif

#ifndef MQTT_SERVER
#define MQTT_SERVER "default_mqtt_server"
#endif

#ifndef CLIENT_ID
#define CLIENT_ID "pico_1" 
#endif

int main() {
    stdio_init_all();
    const uint TRIGG = 15;
    const uint ECHO = 14;
    gpio_init(TRIGG);
    gpio_init(ECHO);
    gpio_set_dir(TRIGG,1);
    gpio_set_dir(ECHO,0);
    //variables for calibration of motionssensor
    int size = 10;
    double tolerance_level = 1;
    double reference_level = 0;
    double* calibration_data;
    //variables for mqtt connection
    mqtt_client_t *client = NULL;
    struct mqtt_connect_client_info_t pico;

    if(connect_to_wifi(SSID,PWD)) {
 
    }
    sleep_ms(1000);
    //sätt upp connection till mqtt
    if(!mqtt_connect(&client, MQTT_SERVER,CLIENT_ID, &pico)) {
            printf("connection setup failed\n");
    }
    sleep_ms(1000);
    calibration_data = run_callibration(TRIGG,ECHO,size);
    if(!calibration_quality_ok(calibration_data,size,2)){
            printf("WARNING:Callibration failed");
            free(calibration_data);
            return 1;
    }
    printf("Callibration completed succesfully\n");

    for(int i = 0; i < size; i++ ) {
        printf("%.2f\n", calibration_data[i]);
    }
    set_reference_level(&reference_level,calibration_data,size);

    printf("reference_level %.2f\n",reference_level);
    free(calibration_data);

    while(1) {

        if(!motion_scan(TRIGG, ECHO, reference_level, tolerance_level)){
            mqtt_pub_motion_read(client,"motion/sensor","motion_detected"); 
            break;
        }
    }

    return 0;
}
