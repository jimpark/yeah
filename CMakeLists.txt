cmake_minimum_required(VERSION 3.4)
project(yeah)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES yeah.cpp)
add_executable(yeah ${SOURCE_FILES})