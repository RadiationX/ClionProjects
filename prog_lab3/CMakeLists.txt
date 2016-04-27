cmake_minimum_required(VERSION 3.5)
project(prog_lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES main.cpp access.h)
add_executable(prog_lab3 ${SOURCE_FILES})