## --------------------------------------------------------------------------
## Driver library for the 24-LED bargraph.
##
## This is a modified version of Adafruits version from
## https://github.com/adafruit/Adafruit_LED_Backpack
##
## Author: Bernhard Bablok
##
## https://github.com/bablokb/pico-24bargraph
## --------------------------------------------------------------------------

# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
#set(PICO_SDK_PATH "/data/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-24bargraph C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# defines for the library
add_compile_definitions(BAR_I2C=i2c1)
add_compile_definitions(BAR_SPEED=400)
add_compile_definitions(BAR_SDA=2)
add_compile_definitions(BAR_SCL=3)
add_compile_definitions(BAR_ADDR=0x70)

#add_compile_definitions(BAR_I2C_PU)      # use builtin-pullups

# Add executable. Default name is the project name, version 0.1

add_executable(pico-24bargraph pico-24bargraph.cpp )

# add preprocessor-constant DEBUG for Debug-builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_VERBOSE_MAKEFILE 1)
  add_compile_definitions(DEBUG)
else()
endif()

pico_set_program_name(pico-24bargraph "pico-24bargraph")
pico_set_program_version(pico-24bargraph "0.1")

pico_enable_stdio_uart(pico-24bargraph 1)
pico_enable_stdio_usb(pico-24bargraph 0)

add_subdirectory(lib)

# Add the standard library to the build
target_link_libraries(pico-24bargraph pico_stdlib)

# Add any user requested libraries
target_link_libraries(pico-24bargraph
        bargraph
        hardware_i2c
        )

pico_add_extra_outputs(pico-24bargraph)

