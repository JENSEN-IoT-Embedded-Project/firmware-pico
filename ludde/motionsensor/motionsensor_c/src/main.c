#include "motionsensor.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    stdio_init_all();
    const uint TRIGG = 15;
    const uint ECHO = 14;
    gpio_init(TRIGG);
    gpio_init(ECHO);
    gpio_set_dir(TRIGG,1);
    gpio_set_dir(ECHO,0);
    int size = 10;
    double reference_level = 0;
    double* calibration_data = run_callibration(TRIGG,ECHO,size);

    if(!calibration_quality_ok(calibration_data,size,2)){
            printf("WARNING:Callibration failed");
            free(calibration_data);
            return 1;
    }
    printf("Callibration completed succesfully\n");

    for(int i = 0; i < size; i++ ) {
        printf("%.2f\n", calibration_data[i]);
    }

    free(calibration_data);
    return 0;
}
