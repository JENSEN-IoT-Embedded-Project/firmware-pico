# libraries
add_library(motionsensor STATIC motionsensor.c)
target_include_directories(motionsensor
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(motionsensor
    pico_stdlib
)

# executable file
add_executable(test main.c)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
    motionsensor
)


