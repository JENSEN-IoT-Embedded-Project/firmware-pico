from machine import Pin,I2C
from lcd_api import LcdApi
from pico_i2c_lcd import I2cLcd
import sys

#function to return the address of the lcd screen
def scan_for_addr(sda_pin,scl_pin) :
    sda = Pin(sda_pin)
    scl = Pin(scl_pin)
    i2c = I2C(0,sda=sda, scl=scl, freq=400000)
    addr = i2c.scan()
    return addr[0]
    
    
# Function to initialize 
def init_lcd(rows,colums,sda_pin,scl_pin) :
    lcd_rows = rows
    lcd_colums = colums
    lcd_addr = scan_for_addr(sda_pin,scl_pin)
    i2c = I2C(0,sda=Pin(sda_pin), scl=Pin(scl_pin), freq=400000)
    return I2cLcd(i2c, lcd_addr,lcd_rows,lcd_colums)

# Function to display info on the lcd screen 
def display_lcd(lcd,row1,row2,length) :
    if (len(row1) or len(row2)) > length:
        print(f"WARNING: max str length = {length} text wont fit on text",file=sys.stderr)
        return
    lcd.clear()
    lcd.move_to(0,0)
    lcd.putstr(str(row1))
    lcd.move_to(0,1)
    lcd.putstr(str(row2))


