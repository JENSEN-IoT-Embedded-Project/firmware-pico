cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

# Importera SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Projektets namn
project(ultrasonic_button_project C CXX ASM)

# Initiera SDK
pico_sdk_init()

# Lägg till din körbara fil (lägg till alla C-filer om du har fler)
add_executable(ultrasonic_button
    main.c
)

# Länka in Pico-standardbiblioteket
target_link_libraries(ultrasonic_button pico_stdlib)

# Om du har andra filer (t.ex. ultrasonic.c) lägg till dem i add_executable ovan.

# Generera UF2, ELF, etc.
pico_add_extra_outputs(ultrasonic_button)

