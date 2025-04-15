from machine import Pin
import socket
import network
import time
import os

# using os.getenv to use ssid and password as env variables
SSID = os.getenv("WIFI_SSID")
PASSWORD = os.getenv("WIFI_PASSWORD")
PORT = 8080
SERVER_IP = "192.168.0.222" # min zero

# set the button pin to pull-up mode
PIN = Pin(16, Pin.IN, Pin.PULL_UP)

# connect to Wi-Fi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASSWORD)

# wait for connection
while not wlan.isconnected():
    print("Waiting for connection...")
    time.sleep(1)

print("Connected to Wi-Fi.")

# function to send HTTP POST when button is pressed
def send_request():
    addr = socket.getaddrinfo(SERVER_IP, PORT)[0][-1]
    s = socket.socket()
    s.connect(addr)
    request = b"POST /button_pressed HTTP/1.1\r\nHost: 192.168.0.222\r\nContent-Length: 0\r\n\r\n"
    s.send(request)
    print("Button press sent to server.")
    s.close()

last_button_state = True

# main loop
while True:
    # check if the button is pressed
    if not PIN.value() and last_button_state:
        try:
            send_request()
            last_button_state = False
        except OSError as e:
            if e.errno == 104:
                print("Error 104: No connection.")
                time.sleep(1)
            else:
                print(f"An error occurred: {e}")
    elif PIN.value():
        last_button_state = True

    time.sleep(0.1)

