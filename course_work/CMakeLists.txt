cmake_minimum_required(VERSION 3.6)
project(course_work)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp parser/Document.h parser/Element.h parser/ElementsList.h parser/ElementHelper.h LinkedList.h Regex-Matcher-master/reg_exp.h Regex-Matcher-master/reg_exp.cpp)
add_executable(course_work ${SOURCE_FILES})