cmake_minimum_required(VERSION 3.15)
project(OpenMPProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fopenmp")
add_executable(OpenMPProject main.cpp)