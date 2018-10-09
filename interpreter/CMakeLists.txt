cmake_minimum_required(VERSION 2.8)

project(interpreter)
include_directories(
    ../include
    )
add_executable(${PROJECT_NAME} "main.cpp")
