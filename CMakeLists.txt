#to set version##
cmake_minimum_required(VERSION 3.31.6)
#to set project name##
project( ascii )
# to find opencvconfig##
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package( OpenCV REQUIRED )
#include libs##
include_directories( ${OpenCV_INCLUDE_DIRS} )
# for .ccp files##
add_executable( ascii src/test.cpp )
# to link those libs okk##
target_link_libraries( ascii ${OpenCV_LIBS} )
