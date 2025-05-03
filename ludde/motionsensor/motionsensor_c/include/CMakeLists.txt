add_library(lcd STATIC lcd.h)
target_link_libraries(lcd
    pico_stdlib
    hardware_i2c
)
target_include_directories(lcd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
