if(LIGHT_SYSTEM STREQUAL PICO_SDK)
        if(LIGHT_PLATFORM STREQUAL TARGET)
                set(PICO_PLATFORM rp2040)
        elseif(LIGHT_PLATFORM STREQUAL HOST)
                set(PICO_PLATFORM host)
        endif()

        #set(PICO_PLATFORM ${PICO_PLATFORM} PARENT_SCOPE)

        include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif()