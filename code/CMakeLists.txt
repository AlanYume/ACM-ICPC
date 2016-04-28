cmake_minimum_required(VERSION 3.5)
project(code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES poj/1011.cpp)

add_executable(code ${SOURCE_FILES})