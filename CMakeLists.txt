cmake_minimum_required(VERSION 3.12)
include(${CMAKE_CURRENT_LIST_DIR}/external/light_preinit.cmake)

project(light_framework_mk2 C CXX ASM)

# libraries
add_subdirectory(lib/light_common)
add_subdirectory(lib/light_object)
add_subdirectory(lib/light_message)

# modules
add_subdirectory(module/light_framework)
add_subdirectory(module/light_platform)

add_subdirectory(platform/arch)
add_subdirectory(platform/chip)
add_subdirectory(platform/board)

# tests
add_subdirectory(test/framework_demo)
