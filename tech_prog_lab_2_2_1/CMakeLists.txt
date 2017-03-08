cmake_minimum_required(VERSION 3.6)
project(tech_prog_lab_2_2_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MergeSort.h Search.h)
add_executable(tech_prog_lab_2_2_1 ${SOURCE_FILES} MergeSort.h Search.h)