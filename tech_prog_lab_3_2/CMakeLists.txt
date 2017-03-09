cmake_minimum_required(VERSION 3.5)
project(tech_prog_lab3_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp LinkedList.h)
add_executable(tech_prog_lab3_2 ${SOURCE_FILES})