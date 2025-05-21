cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

set(PICO_CYW43_SUPPORTED 1)
set(PICO_LWIP_MQTT 1)

include(pico_sdk_import.cmake)

project(ultrasonic_sensor C CXX ASM)

pico_sdk_init()

include_directories(include)

add_subdirectory(src)

