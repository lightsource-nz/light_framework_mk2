cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(light_framework_mk2 C CXX ASM)

pico_sdk_init()

# libraries
add_subdirectory(lib/light_object)
add_subdirectory(lib/light_message)
add_subdirectory(lib/light_util)

# modules
add_subdirectory(module/light_framework)

# tests
add_subdirectory(test/framework_demo)
