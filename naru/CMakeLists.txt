cmake_minimum_required(VERSION 3.13)
set(CMAKE_ASM_COMPILER /usr/bin/arm-none-eabi-as)
project(pico_mqtt C CXX ASM)
set(PICO_BOARD pico_w)
include(/home/narulinux/github/pico-sdk/external/pico_sdk_import.cmake)

pico_sdk_init()
add_executable(pico_mqtt motionsensor.c)

# Enable USB output for debugging (if needed)
pico_enable_stdio_usb(pico_mqtt 1)

# Link required libraries
target_link_libraries(pico_mqtt 
    pico_stdlib 
    pico_cyw43_arch_none  
    mosquitto  
)


pico_add_extra_outputs(pico_mqtt)
