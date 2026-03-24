# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK 
include(pico_sdk_import.cmake)






# FreeRTOS 
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)
set(FREERTOS_PORT GCC_ARM_CM33_NTZ_NONSECURE CACHE STRING "FreeRTOS port")
include(FreeRTOS_Kernel_import.cmake)

project(pico2_freertos_test C CXX ASM)

pico_sdk_init()

# xEventGroupSetBitsFromISR()  xTimerPendFunctionCallFromISR() error  
target_sources(FreeRTOS-Kernel PRIVATE
        ${FREERTOS_KERNEL_PATH}/event_groups.c
        ${FREERTOS_KERNEL_PATH}/timers.c
        ${FREERTOS_KERNEL_PATH}/stream_buffer.c
)






add_executable(pico2_freertos_test
        pico2_freertos_test.c
)

pico_set_program_name(pico2_freertos_test "pico2_freertos_test")
pico_set_program_version(pico2_freertos_test "0.1")

pico_enable_stdio_uart(pico2_freertos_test 1)
pico_enable_stdio_usb(pico2_freertos_test 0)

target_include_directories(pico2_freertos_test PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(pico2_freertos_test
        pico_stdlib
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
)

pico_add_extra_outputs(pico2_freertos_test)