#include "pico/stdlib.h"
#include <stdio.h>
#include "func.h"

void buzz(int buzz_dur) {
	gpio_put(buzzer, 1);  
	sleep_ms(buzz_dur);       
	gpio_put(buzzer, 0); 
}
