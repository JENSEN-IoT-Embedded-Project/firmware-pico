import time
import utime
from machine import I2C, Pin, ADC
from I2C_LCD import I2CLcd

i2c = I2C(1, sda=Pin(14), scl=Pin(15), freq=400000)
devices = i2c.scan()

try:
    if devices != []:
        lcd = I2CLcd(i2c, devices[0], 2, 16)     
except:
    pass
    

menu = ["Alarm", "Settings"]
menu_items = len(menu) - 1

def led_screen(joystick_arg, counter):
    count = counter
    if joystick_arg == "left":
        count -= 1
    elif joystick_arg == "right":
        count += 1
    elif joystick_arg == "button_pressed":
        return True
    
    if count < 0:
        return menu_items
    elif count > menu_items:
        return 0
    else:
        return count

def display_led_screen(counter):
    lcd.clear()
    lcd.putstr(menu[counter])
