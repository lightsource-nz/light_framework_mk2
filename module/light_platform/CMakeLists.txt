
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

function(light_add_arch ARCH BITS MMU CALLBACK)
        message(added arch ${ARCH})
        list(APPEND LIGHT_ARCH_LIST ${ARCH})
        set(LIGHT_ARCH_BITS__${ARCH} ${BITS})
        set(LIGHT_ARCH_MMU__${ARCH} ${MMU})
        set(LIGHT_ARCH_CALLBACK__${ARCH} ${CALLBACK})
        set(LIGHT_ARCH_LIST ${LIGHT_ARCH_LIST} PARENT_SCOPE)
        set(LIGHT_ARCH_CALLBACK__${ARCH} ${LIGHT_ARCH_CALLBACK__${ARCH}} PARENT_SCOPE)
endfunction()
function(light_add_chip CHIP ARCH CALLBACK)
        message(added chip ${CHIP})
        list(APPEND LIGHT_CHIP_LIST ${CHIP})
        set(LIGHT_CHIP_ARCH__${CHIP} ${ARCH})
        set(LIGHT_CHIP_CALLBACK__${CHIP} ${CALLBACK})
        set(LIGHT_CHIP_LIST ${LIGHT_CHIP_LIST} PARENT_SCOPE)
        set(LIGHT_CHIP_ARCH__${CHIP} ${LIGHT_CHIP_ARCH__${CHIP}} PARENT_SCOPE)
        set(LIGHT_CHIP_CALLBACK__${CHIP} ${LIGHT_CHIP_CALLBACK__${CHIP}} PARENT_SCOPE)
endfunction()
function(light_add_board BOARD CHIP CALLBACK)
        message(added board ${BOARD})
        list(APPEND LIGHT_BOARD_LIST ${BOARD})
        set(LIGHT_BOARD_CHIP__${BOARD} ${CHIP})
        set(LIGHT_BOARD_CALLBACK__${BOARD} ${CALLBACK})
        set(LIGHT_BOARD_LIST ${LIGHT_BOARD_LIST} PARENT_SCOPE)
        set(LIGHT_BOARD_CHIP__${BOARD} ${LIGHT_BOARD_CHIP__${BOARD}} PARENT_SCOPE)
        set(LIGHT_BOARD_CALLBACK__${BOARD} ${LIGHT_BOARD_CALLBACK__${BOARD}} PARENT_SCOPE)
endfunction()
function(light_set_arch ARCH)
        set(LIGHT_ARCH ${ARCH})
        set(LIGHT_ARCH ${LIGHT_ARCH} PARENT_SCOPE)
        target_link_libraries(
                light_platform
                INTERFACE
                arch_${ARCH}
        )
        cmake_language(CALL ${LIGHT_ARCH_CALLBACK__${ARCH}})
endfunction()
function(light_set_chip CHIP)
        set(LIGHT_CHIP ${CHIP})
        set(LIGHT_CHIP ${LIGHT_CHIP} PARENT_SCOPE)
        light_set_arch(LIGHT_CHIP_ARCH__${CHIP})
        target_link_libraries(
                light_platform
                INTERFACE
                chip_${CHIP}
        )
        cmake_language(CALL ${LIGHT_CHIP_CALLBACK__${CHIP}})
endfunction()
function(light_set_board BOARD)
        set(LIGHT_BOARD ${BOARD})
        set(LIGHT_BOARD ${LIGHT_BOARD} PARENT_SCOPE)
        light_set_chip(LIGHT_BOARD_CHIP__${BOARD})
        target_link_libraries(
                light_platform
                INTERFACE
                board_${BOARD}
        )
        cmake_language(CALL ${LIGHT_BOARD_CALLBACK__${BOARD}})
endfunction()
