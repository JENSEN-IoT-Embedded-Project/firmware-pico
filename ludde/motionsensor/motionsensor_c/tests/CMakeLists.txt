
add_executable(test wifi.c)
#before your run cmake
add_compile_definitions(SSID=\"$ENV{WIFI_SSID}\")
add_compile_definitions(PWD=\"$ENV{WIFI_PASSWORD}\")

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    hardware_i2c
    lwipopts
    lcd
)
