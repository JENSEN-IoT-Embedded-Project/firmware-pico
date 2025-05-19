include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ultrasonic_button
    main.c
    pico_sensor.c 
    mqtt_connect.c
    jsonify.c
    buzzer_melodies.c
)

target_link_libraries(ultrasonic_button
	pico_stdlib
	pico_cyw43_arch_lwip_threadsafe_background
	hardware_gpio
	pico_lwip_mqtt
    hardware_pwm
)

pico_enable_stdio_usb(ultrasonic_button 1)
pico_enable_stdio_uart(ultrasonic_button 0)

pico_add_extra_outputs(ultrasonic_button)
