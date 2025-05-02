include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ultrasonic_button
    main.c
    pico_sensor.c 
)

target_link_libraries(ultrasonic_button
	pico_stdlib
)

pico_add_extra_outputs(ultrasonic_button)
