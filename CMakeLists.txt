cmake_minimum_required(VERSION 2.8.7)
project(getopty C)

set(CMAKE_C_FLAGS "-Wall -std=c99")

enable_testing()
add_subdirectory(test)
