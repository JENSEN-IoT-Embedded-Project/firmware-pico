from hcsr04 import distance_to_object
from lcd_16x2 import init_lcd, display_lcd 
from buzzer_alarm import buzzer_signal
from machine import Pin

lcd = init_lcd(2,16,0,1)
buzzer = Pin(13,Pin.OUT)
itr = 0
max_diff = 5;
btn = Pin(17,Pin.IN,Pin.PULL_UP)
alarm_activated = False

while True:
        
        distance = round(distance_to_object(15,14),2) 
        if itr == 0 :
            itr += 1
            initial_distance = distance

        display_lcd(lcd,"Distance", distance, 16)

        if(initial_distance  - distance) > max_diff :
            alarm_activated = True
            while alarm_activated :
                display_lcd(lcd,"WARNING","ALARM ACTIVATED",16)
                buzzer_signal(buzzer)
                if btn.value() == 0 :
                    itr = 0
                    alarm_activated = False




