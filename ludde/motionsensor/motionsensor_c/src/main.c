#include "motionsensor.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/cyw43_arch.h"
#include "wifi.h"

#ifndef SSID
#define SSID "default_ssid"
#endif

#ifndef PWD
#define PWD "default_pwd"
#endif

int main() {
    stdio_init_all();
    const uint TRIGG = 15;
    const uint ECHO = 14;
    gpio_init(TRIGG);
    gpio_init(ECHO);
    gpio_set_dir(TRIGG,1);
    gpio_set_dir(ECHO,0);
    int size = 10;
    double tolerance_level = 1;
    double reference_level = 0;
    double* calibration_data;

    if(connect_to_wifi(SSID,PWD)) {
        
    }
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
            break;
        }
    }
    printf("motion_detected\n");

    return 0;
}
