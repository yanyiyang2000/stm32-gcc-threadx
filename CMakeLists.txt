cmake_minimum_required(VERSION 3.22)

# uncomment to make cmake output verbose
#set(CMAKE_VERBOSE_MAKEFILE ON)

# skip compiler test for cross compilation
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# set compiler path and executable extension
set(CMAKE_ASM_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_C_COMPILER   "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)
set(CMAKE_EXECUTABLE_SUFFIX_C   .elf)

project(
    test
    LANGUAGES C ASM
)

file(
    GLOB SRC
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32L4xx/Source/system_stm32l4xx.c
    ${CMAKE_CURRENT_LIST_DIR}/User/source/threadx/*.S
    ${CMAKE_CURRENT_LIST_DIR}/User/source/gpio_config.c
    ${CMAKE_CURRENT_LIST_DIR}/User/source/clock_config.c
    ${CMAKE_CURRENT_LIST_DIR}/User/source/main.c
)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/User/include
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32L4xx/Include
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Core/Include/m-profile
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Core/Include
    ${CMAKE_CURRENT_LIST_DIR}/ThreadX/common/inc
    ${CMAKE_CURRENT_LIST_DIR}/ThreadX/ports/cortex_m4/gnu/inc
)

link_directories(${CMAKE_CURRENT_LIST_DIR}/ThreadX/lib)
link_libraries(threadx)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_compile_definitions(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    STM32L476xx
)

target_compile_options(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mthumb
    -O0
    -g3
    -Wall
    -ffunction-sections
    -fdata-sections
)

target_link_options(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mthumb
    -nostartfiles               # use custom startup file
    --specs=nano.specs          # use libc_nano.a instead of libc.a
    --specs=nosys.specs         # use libnosys.a
    -Wl,--gc-sections           # enable garbage collection of unused sections
    -Wl,--trace                 # print name of input files (use --verbose for more detailed information)
    -Wl,--print-memory-usage    # print memory usage
    # -Wl,--print-map             # print memory map
    -T "${CMAKE_CURRENT_LIST_DIR}/User/source/threadx/threadx.ld"
)
