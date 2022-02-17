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

cmake_minimum_required(VERSION 3.13)

include(${PICO_SDK_INIT_CMAKE_FILE})

project(bargraph)
add_library(${PROJECT_NAME} src/Adafruit_24bargraph.cpp src/I2CDevice.cpp)
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
