cmake_minimum_required(VERSION 3.5)
project(prog_lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp access.cpp)
add_executable(prog_lab3 ${SOURCE_FILES})