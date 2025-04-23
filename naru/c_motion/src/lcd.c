#include "pico/stdlib.h"
#include <stdio.h>
#include "func.h"


void lcd_search(char* buffer){
	lcd_clear();
	lcd_set_cursor(0, 0);
	lcd_print("distance:");
	lcd_set_cursor(1, 0);
	lcd_print(buffer);
}

void lcd_alarm(char* buffer){
	lcd_clear();
	lcd_set_cursor(0, 0);
	lcd_print("triggered at:");
	lcd_set_cursor(1, 0);
	lcd_print(buffer);
}
