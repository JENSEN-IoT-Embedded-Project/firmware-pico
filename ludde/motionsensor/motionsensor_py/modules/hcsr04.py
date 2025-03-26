from machine import Pin
import utime


def distance_to_object(pin_out,pin_in) :
    trigger = Pin(pin_out, Pin.OUT)
    echo = Pin(pin_in,Pin.IN)

    trigger.low()
    utime.sleep_us(2)
    trigger.high()
    utime.sleep_us(10)
    trigger.low()

    while echo.value() == 0 :
        signalOff = utime.ticks_us()
    while echo.value() == 1 :
        signalOn = utime.ticks_us()

    timePassed = signalOn - signalOff
    distance_cm = (timePassed * 0.0343)/2
    utime.sleep(1)
    return round(distance_cm, 2) 



'''while True :
    print(distance_to_object(15,14))
'''
