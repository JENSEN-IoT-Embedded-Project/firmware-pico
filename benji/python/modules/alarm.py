from machine import Pin, PWM
import utime

Buzzer = Pin(16, Pin.OUT)
pwm = PWM(Buzzer)

def play():
    cmajor = [261, 293, 329, 349, 392, 440, 493]

    for freq in cmajor:
        pwm.freq((freq * 2) * 2)
        pwm.duty_u16(8024)
        utime.sleep_ms(100)
        pwm.duty_u16(0)
