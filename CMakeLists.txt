cmake_minimum_required(VERSION 3.20)

project("Weather-Station-STM32F0" C CXX ASM)

include(cmake/st-project.cmake)
set(EXECUTABLE_NAME station)

add_executable(${EXECUTABLE_NAME})
add_st_target_properties(${EXECUTABLE_NAME})