cmake_minimum_required(VERSION 3.21)
project(eco)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps)

add_executable(eco
        src/main.cpp
        src/blob/logic.h
        src/blob/brain.h
        src/blob/graphics.h
        src/world.cpp
        src/globals.cpp
        include/globals.h
        src/blob/blob.h
        src/collision.h
        )

target_include_directories(eco PUBLIC
        deps/SFML/include
        deps/imgui
        deps/imgui-sfml
        include
        )
target_link_libraries(eco
        sfml-system
        sfml-window
        sfml-graphics
        )
