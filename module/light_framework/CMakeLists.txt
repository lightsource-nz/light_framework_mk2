
add_library(light_framework INTERFACE)

set(LIGHT_FRAMEWORK_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
function(light_framework_application_module TARGET)
    if(NOT PICO_NO_HARDWARE)
        #pico_set_linker_script(${TARGET} ${LIGHT_FRAMEWORK_MODULE_DIR}/memmap_light.ld)
    endif()
    target_link_libraries(${TARGET} INTERFACE ${LIGHT_FRAMEWORK_MODULE_DIR}/objects.${PICO_PLATFORM}.ld)
endfunction()

target_include_directories(
    light_framework INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(
    light_framework INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/framework.c
)

target_link_libraries(
    light_framework INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/objects.${PICO_PLATFORM}.ld
    light_common
    light_object
)

