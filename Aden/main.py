from machine import Pin, I2C
import time
import network
import ubinascii
from simple import MQTTClient
from pico_i2c_lcd import I2cLcd  
import ssl
import telegram
import urequests
import uasyncio as asyncio


class WiFiConnection:
    def __init__(self, ssid, password):
        self.ssid = "XXXXXXXXXXXX"
        self.password = "XXXXXXXXXXXX"
        self.wlan = network.WLAN(network.STA_IF)

    def connect(self):
        self.wlan.active(True)
        self.wlan.connect(self.ssid, self.password)
        while not self.wlan.isconnected():
            print("Waiting for WiFi connection...")
            time.sleep(1)
        print("Connected to WiFi:", self.wlan.ifconfig())

# MQTT Credentials
mqtt_host = "56d7c5afd00f49f2aeec96b9ac10f4b7.s1.eu.hivemq.cloud"
mqtt_port = 8883
mqtt_username = "Verysure_MQTT"  
mqtt_password = "X*WQUmA&uQ#hJW4" 
mqtt_publish_topic = "pico/sensor/distance" 
mqtt_client_id = "somethingreallyrandomandunique123"

context = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
context.verify_mode = ssl.CERT_NONE

# Initialize our MQTTClient and connect to the MQTT server
mqtt_client = MQTTClient(
        client_id=mqtt_client_id,
        server=mqtt_host,
        port=mqtt_port,
        user=mqtt_username,
        password=mqtt_password,
        ssl=context)

mqtt_client.connect()


# Class for ultrasonic sensor
class Ultrasonic:
    def __init__(self, trig_pin, echo_pin, timeout=3000):
        self.trig = Pin(trig_pin, Pin.OUT)
        self.echo = Pin(echo_pin, Pin.IN)
        self.timeout = timeout

    def timing(self):
        self.trig.low()
        time.sleep_us(2)
        self.trig.high()
        time.sleep_us(10)
        self.trig.low()
        
        start_time = time.ticks_us()
        while self.echo.value() == 0:
            if time.ticks_diff(time.ticks_us(), start_time) > self.timeout:
                return self.timeout
        pulse_start = time.ticks_us()
        
        while self.echo.value() == 1:
            pass
        pulse_end = time.ticks_us()

        return time.ticks_diff(pulse_end, pulse_start)
    
    def ranging(self, unit=1):
        duration = self.timing()
        if unit == 1:
            return duration / 58.0  # Distance in cm
        else:
            return duration / 74 / 2  # Distance in inches

# Initialize ultrasonic sensor
sensor = Ultrasonic(12, 13)  # GPIO pin 12 and 13

# Initialize buzzer
buzzer = Pin(0, Pin.OUT)
buzzer.value(0)

# Initialize I2C LCD
I2C_ADDRESS = 0x27
LCD_COLUMNS = 16
LCD_ROWS = 2

i2c = I2C(0, scl=Pin(5), sda=Pin(4))
lcd = I2cLcd(i2c, I2C_ADDRESS, LCD_ROWS, LCD_COLUMNS)

lcd.backlight_on()


# Telegram bot setup
TELEGRAM_BOT_TOKEN = "XXXXXXXXXXXXXXXX"
CHAT_ID = "XXXXXXXXXXXXXXXX"  # Your chat ID
bot = telegram.TelegramBot(TELEGRAM_BOT_TOKEN, callback=None)

async def send_notification():
    asyncio.create_task(bot.run())  # Start the bot loop
    bot.send(CHAT_ID, f"Alert! Intruder detected at {distance:.2f} cm.")  # Send a message
    await asyncio.sleep(1)    


try:
    while True:
        
        time.sleep(1)
        distance = sensor.ranging(1)
        
        
        current_time = time.localtime()
        timestamp = "{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}".format(
            current_time[0], current_time[1], current_time[2],  # Year-Month-Day
            current_time[3], current_time[4], current_time[5]   # Hour:Minute:Second
        )
        
        if distance <= 10:
            asyncio.run(send_notification())
        
        lcd.clear()
        lcd.move_to(0, 0)  
        lcd.putstr("Distance (cm):")

        lcd.move_to(0, 1)  
        lcd.putstr(f"{distance:.2f} cm")  

        # Buzzer alert
        if distance <= 10:
            buzzer.value(1)
            time.sleep(0.1)
            buzzer.value(0)
            time.sleep(0.1)
        else:
            buzzer.value(0)
            
        
        
        # Publish the data to the topic!
        print(f"Publish {timestamp}, Distance: {distance:.2f} cm")
        mqtt_client.publish(mqtt_publish_topic, str(distance))
        
        
except Exception as e:
    print(f'Failed to publish message: {e}')
finally:
    mqtt_client.disconnect()
