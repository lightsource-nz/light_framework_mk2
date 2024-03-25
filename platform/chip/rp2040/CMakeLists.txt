add_library(light_chip_rp2040 INTERFACE)
                  
target_include_directories(
    light_chip_rp2040
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
 
target_sources(
    light_chip_rp2040
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/rp2040.c
)

target_link_libraries(
    light_chip_rp2040
    INTERFACE
    light_common
)

if(LIGHT_SYSTEM STREQUAL PICO_SDK)
        target_link_libraries(
                light_chip_rp2040
                INTERFACE
                pico_platform
                pico_sync
        )
endif()
