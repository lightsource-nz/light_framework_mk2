
add_library(light_platform INTERFACE)

target_include_directories(
        light_platform INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(
        light_platform INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/platform.c
)

target_link_libraries(
        light_platform INTERFACE
        light_framework
)
