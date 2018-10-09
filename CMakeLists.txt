cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 11)
project(ur5_manipulator)
find_package(Threads REQUIRED)

#find_package(Qt5Core)
add_subdirectory(interpreter)
include_directories(
    include
)

add_library(
  ur_robot
    include/ur_robot.cpp
    include/ur_robot.h
)

#qt5_use_modules(qtsampleplayer Core Widgets Multimedia MultimediaWidgets Gui OpenGL)
add_executable(example example.cpp )
add_executable(plot plot.cpp )
add_executable(blend blending.cpp)
add_executable(force force.cpp)
target_link_libraries(force ur_robot pthread)
target_link_libraries( example  ur_robot pthread)
target_link_libraries( plot  ur_robot pthread)
target_link_libraries( blend  ur_robot pthread)

