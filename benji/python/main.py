from modules import alarm, hcsr04, joystick_pos, LCD_led
import utime

isArmed = False
counter = 0

LCD_led.display_led_screen(counter)

while True:
    utime.sleep_ms(10)
    
    distance = hcsr04.measure_distance()
    if distance < 20:
        if isArmed:
            alarm.play()
    
    thumbstick_command = None
    thumbstick_command = joystick_pos.get_thumbstick_position()
    
    if thumbstick_command is not None:
        
        if thumbstick_command == "button_pressed":
            isArmed = not isArmed
        counter = LCD_led.led_screen(thumbstick_command, counter)
        LCD_led.display_led_screen(counter)
    
    utime.sleep_ms(100)
