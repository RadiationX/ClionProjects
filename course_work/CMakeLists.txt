cmake_minimum_required(VERSION 3.6)
project(course_work)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp parser/Document.h parser/Element.h parser/ElementsList.h parser/ElementHelper.h)
add_executable(course_work ${SOURCE_FILES})