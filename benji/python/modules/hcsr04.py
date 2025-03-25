from machine import Pin
import utime

Trigger = Pin(13, Pin.OUT)
Echo = Pin(12, Pin.IN)

def measure_distance():
    time_start = 0
    time_end = 0
    
    Trigger.value(1)
    utime.sleep_us(10)
    Trigger.value(0)
    while Echo.value() == 0:
        pass
    time_start = utime.ticks_us()
    while Echo.value() == 1:
        pass
    time_end = utime.ticks_us()
    time_passed = time_end - time_start
    distance = (time_passed * 0.0343) / 2 
    
    return distance
