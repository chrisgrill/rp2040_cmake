cmake_minimum_required(VERSION 3.12)
set(PICO_SDK_PATH "/home/chris/Projects/pico/pico-sdk")
include(pico_sdk_import.cmake)

project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()
add_executable(blink blink.cpp LSM6DSOX.cpp LSM6DSOX.h)
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)
target_link_libraries(blink pico_stdlib hardware_i2c)

pico_add_extra_outputs(blink)
