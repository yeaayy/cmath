cmake_minimum_required(VERSION 3.15)
project(CMath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options("$<BUILD_INTERFACE:-Wall;-ggdb>")

add_executable(cmath)
add_subdirectory(src)
add_subdirectory(test)