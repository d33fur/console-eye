cmake_minimum_required(VERSION 3.16)

project(untitled2)

set(CMAKE_CXX_STANDARD 20)

#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavdevice
        libavfilter
        libavformat
        libavcodec
        libswresample
        libswscale
        libavutil)

add_executable(untitled2 main.cpp)
target_link_libraries(untitled2 ${OpenCV_LIBS})
target_link_libraries(untitled2 ${CURSES_LIBRARIES})
#install()
