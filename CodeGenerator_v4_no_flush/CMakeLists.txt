cmake_minimum_required(VERSION 3.3)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/CPoint.h src/CLine.h src/CMatrix.h src/Reader.h)
add_executable(HTransformer ${SOURCE_FILES})