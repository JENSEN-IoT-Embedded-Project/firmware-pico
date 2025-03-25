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

button_pressed = False
alarm_status = False
menu_items = 1

def led_screen(joystick_arg, counter):
    
    global button_pressed, alarm_status
    alarm_status = True if button_pressed else False
    count = counter
    
    if joystick_arg == "left":
        count -= 1
    elif joystick_arg == "right":
        count += 1
    elif joystick_arg == "button_pressed":
        if count == 0 and button_pressed == False:
            button_pressed = not button_pressed
            alarm_status = not alarm_status
        else:
            button_pressed = not button_pressed
            alarm_status = not alarm_status
        
    
    if count < 0:
        return menu_items
    elif count > menu_items:
        return 0
    else:
        return count

def display_led_screen(counter):
    lcd.clear()
    menu = [(f"Alarm armed:    {alarm_status}"), "Settings"]
    lcd.putstr(menu[counter])
