from machine import Pin, PWM
import utime

Buzzer = Pin(15, Pin.OUT)
pwm = PWM(Buzzer)

dm_scale_frequencies = {   
    "B_flat4": 466.164, 
    "C5": 523.251,   
    "D5": 587.330,   
    "E5": 659.255,   
    "F5": 698.456,    
}


def play_tone(frequency, duration_ms):
    pwm.freq(int(frequency)) 
    pwm.duty_u16(32768)  
    utime.sleep_ms(duration_ms) 
    pwm.duty_u16(0) 

def play():
    melody = [
        ("D5", 400), ("D5", 400), ("D5", 400), ("B_flat4", 300),
        ("F5", 80), ("D5", 400), ("B_flat4", 300), ("F5", 80),
        ("D5", 400), 
    ]
    
    for note, duration in melody:
        frequency = dm_scale_frequencies[note]
        play_tone(frequency, duration)
        utime.sleep_ms(50)
