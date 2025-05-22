#Components:For the motion sensor

##Hardware:

1. Raspberry Pi Pico W

2. Raspberry Pi Zero
 
3. RGB light(For more visual effects not necessary but I think it's cool)

4. Resistors

5. A buzzer

6. Ultrasonic motion sensor

7. Cables

8. A lcd screen (not necessary but good to have)
   
##Software:   

1.Thony IDE 

2. MicroPython (Which is more compatible with the microcontroller pico w)

3.WSL(To run the MQTT broker and scripts)

4.VS code(Not mandatory but i ran my program in VS code also)

5.Twilio API

6.InfluxDB(In Docker Container)

7.Web Application HTTP Server

#Complete description of all hardware and software needed for motion sensor project


Hardware Components:
1.Raspberry Pi Pico W – A low-cost microcontroller board with built-in Wi-Fi, ideal for sensor-based projects.

2.Raspberry Pi Zero – A compact and efficient single-board computer that can be used for processing data from sensors.

3.RGB Light – Adds visual effects by changing colors in response to motion detection.

4.Resistors – Essential for controlling voltage levels and preventing damage to circuit components.

5.Buzzer – Emits an audible alert when motion is detected.

6.Ultrasonic Motion Sensor – Detects movement using ultrasonic waves; triggers the system when an object moves within a certain range.

7.Cables – Used to connect various components and ensure proper electrical communication.

8.LCD Screen (Optional) – Displays information such as motion detection logs, system status, or messages.

Software Components:

1.Thonny IDE – A lightweight and beginner-friendly Python IDE, useful for writing and testing MicroPython scripts.

2.MicroPython – A compact version of Python optimized for microcontrollers like the Raspberry Pi Pico W.

3.C/C++ – Provides low-level control and efficiency for programming the Raspberry Pi Pico W.

4.Pico-SDK – A set of development tools, libraries, and examples for programming Raspberry Pi Pico with C/C++.

5.WSL (Windows Subsystem for Linux) – Provides a Linux-like environment on Windows, used to run the MQTT broker and scripts.

6.VS Code (Optional) – A powerful code editor used for developing, debugging, and running scripts.

7.Twilio API – Enables SMS notifications or alerts when motion is detected.

8.InfluxDB (Docker Container) – A time-series database used to store and analyze motion detection data.

9.Web Application HTTP Server – Hosts a web interface to display motion sensor logs and real-time status.

#System Description:

1. Detecting Motion (The Watcher)
The Ultrasonic Motion Sensor is like a guard—it keeps scanning for movement. If something moves, the Raspberry Pi Pico W picks it up and sends the signal.

2. Immediate Response (Lights & Sound)
The RGB light changes its color according to the distance of the detected object. The buzzer's sound also varies based on the object's distance, alerting people nearby that something's up

3. Sending Data ( Via WhatsApp or direct SMS)
The Pico W sends motion data to the Raspberry Pi Zero. The MQTT Broker acts like a postman—delivering this message to all connected devices.

4. Storing Data (The Memory)
The system logs all motion events in Influx DB TSDB, a special database that remembers each detection for later analysis.

5. User Notification (The Alert System)
A Python script running on the Raspberry Pi Zero listens for motion. When movement is detected, it triggers the Twilio API, sending an instant SMS or WhatsApp notification to the user.

6. Web Dashboard (Control Centre)
A Web Application lets users check real-time updates. User can see motion logs, status, and alerts from any device.

So, in simple terms: Our motion sensor detects movement, lights and sounds react, data gets sent, stored, and analysed, and finally—the-user get notified immediately.
It’s like having a smart security assistant that’s always watching and ready to notify the user the moment it spots something!


#System Diagram Mermaid: 

```mermaid
graph TD;
    A[Ultrasonic Motion Sensor] -->|Detects motion| B[Raspberry Pi Pico W]
    B -->|Triggers alert| C[RGB Light]
    B -->|Triggers sound| D[Buzzer]
    B -->|Sends data| E[MQTT Broker - Raspberry Pi Zero]
    E -->|Distributes data| F[Web Application]
    E -->|Stores data| G[InfluxDB - TSDB]
    F -->|Displays real-time motion logs| H[User Web Dashboard]
    E -->|Triggers Twilio API| I[User Notification System]
    I -->|Sends message| J[WhatsApp/SMS Notification]

    style A fill:#f4a26145,stroke:#5,stroke-width:2px
    style B fill:#e76f5167,stroke:#333223,stroke-width:2px
    style E fill:#2a9d8f88,stroke:#333,stroke-width:2px
    style I fill:#264653,stroke:#fff,stroke-width:2px

    ```



