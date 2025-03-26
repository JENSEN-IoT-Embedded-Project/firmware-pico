from machine import Pin
import utime

def buzzer_signal(buzzer) :
        buzzer.high()
        utime.sleep_ms(100)
        buzzer.low()
        utime.sleep_ms(100)




    
            
