cmake_minimum_required(VERSION 3.5)
project(tech_prog_lab_1_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MergeSort.cpp MergeSort.h)
add_executable(tech_prog_lab_1_2 ${SOURCE_FILES} MergeSort.cpp MergeSort.h)