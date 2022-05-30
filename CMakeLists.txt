cmake_minimum_required(VERSION 3.21)
project(eco)

set(CMAKE_CXX_STANDARD 20)

add_executable(eco main.cpp blob/logic.h blob/brain.h blob/graphics.h world.cpp globals.cpp globals.h blob/blob.h collision.h)
