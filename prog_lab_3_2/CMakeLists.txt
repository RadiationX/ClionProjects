cmake_minimum_required(VERSION 3.5)
project(prog_lab_3_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Queue.h)
add_executable(prog_lab_3_2 ${SOURCE_FILES})