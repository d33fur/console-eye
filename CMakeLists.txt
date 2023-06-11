cmake_minimum_required(VERSION 3.22)
project(consoleapp)

set(CMAKE_CXX_STANDARD 20)

add_executable(consoleapp main.cpp Vec2.h Vec3.h VecMath.h)
