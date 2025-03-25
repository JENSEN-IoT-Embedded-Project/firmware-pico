from machine import Pin,I2C
from lcd_api import LcdApi
from pico_i2c_lcd import I2cLcd

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

lcd = init_lcd(2,16,0,1)

lcd.clear()
lcd.putstr("hello")

# Function to initialize LCD object and variables





