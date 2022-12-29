cmake_minimum_required(VERSION 3.24)
project(AED2223_G60)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AED2223_G60
        AirLine.cpp
        AirLine.h
        Airport.cpp
        Airport.h
        Flight.cpp
        Flight.h
        Manager.cpp
        Manager.h
        main.cpp)
