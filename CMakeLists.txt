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
        src/blob/blob.h
        src/collision.h
        include/globals.h
        )

target_include_directories(eco PRIVATE
        deps/SFML/include
        deps/imgui-sfml
        deps/imgui
        include
        )

target_link_libraries(eco PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        ImGui-SFML
        )