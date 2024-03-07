cmake_minimum_required(VERSION 3.27)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        const.h
        main.cpp
        robot.cpp
        robot.h)
