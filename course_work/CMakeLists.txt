cmake_minimum_required(VERSION 3.6)
project(course_work)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp parser/Element.h parser/ElementHelper.h parser/Parser.h)
add_executable(course_work ${SOURCE_FILES})