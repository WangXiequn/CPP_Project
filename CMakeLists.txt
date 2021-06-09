cmake_minimum_required(VERSION 3.16.3)
project(CPP_Project)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_Project main.cpp Matrix.h)