# libraries
add_library(motionsensor STATIC motionsensor.c)
target_include_directories(motionsensor
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(motionsensor
    pico_stdlib
)

add_library(wifi STATIC wifi.c)
target_include_directories(wifi PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(wifi
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    lwipopts
)

add_library(mqtt STATIC mqtt.c)
target_include_directories(mqtt PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mqtt
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    lwipopts
    pico_lwip_mqtt
)
# executable file

add_executable(test main.c)
add_compile_definitions(MQTT_SERVER=\"$ENV{MQTT_SERVER}\")
add_compile_definitions(SSID=\"$ENV{WIFI_SSID}\")
add_compile_definitions(PWD=\"$ENV{WIFI_PASSWORD}\")

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    lwipopts
    pico_lwip_mqtt
    mqtt
    wifi
    motionsensor
)


