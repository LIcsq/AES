cmake_minimum_required(VERSION 3.26)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled2 main.cpp
        constants.h
        key_expansion.h
        key_expansion.cpp
        aes_operations.h
        aes_operations.cpp
        utilities.h
        utilities.cpp)
