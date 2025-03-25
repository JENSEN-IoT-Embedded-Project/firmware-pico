import utime
from machine import I2C, Pin, ADC

xAxis = ADC(Pin(28))
yAxis = ADC(Pin(27))
button = Pin(26,Pin.IN, Pin.PULL_UP)


def get_thumbstick_position(): 
    
    xValue = xAxis.read_u16()
    yValue = yAxis.read_u16()
    isCenter = True if (xValue < 34000 and xValue > 33000) and (yValue < 34500 and xValue > 33000) else False
    
    if button.value() == 0:
        return "button_pressed"
    
    if not isCenter:
        if xValue < 600:
            return "left"
        elif xValue > 60000:
            return "right"
        elif yValue > 60000:
            return "down"
        elif yValue < 600:
            return "up"
