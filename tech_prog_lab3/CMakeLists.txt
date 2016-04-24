cmake_minimum_required(VERSION 3.5)
project(tech_prog_lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp LinkedList.h Block.h ListItem.h)
add_executable(tech_prog_lab3 ${SOURCE_FILES})