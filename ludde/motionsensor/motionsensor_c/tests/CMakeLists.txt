add_executable(tests soniclcd.c)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    hardware_i2c
    lwipopts
    lcd
)
