#ifndef FUNC_H
#define FUNC_H

#include "pico/stdlib.h"

extern const uint buzzer;
extern const uint trigger;
extern const uint echo;
extern const uint SDA_PIN;
extern const uint SCL_PIN;

void buzz(int buzz_dur);  
float measureDistance(void);  
void lcd_search(char* buffer);
void lcd_alarm(char* buffer);
#endif
