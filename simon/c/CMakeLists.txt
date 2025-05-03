cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(ultrasonic_sensor C CXX ASM)

pico_sdk_init()

include_directories(include)

add_subdirectory(src)

