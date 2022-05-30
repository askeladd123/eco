cmake_minimum_required(VERSION 3.21)
project(eco)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        deps/SFML/include
        deps/imgui
        deps/imgui/backends
        deps/imgui-sfml
        deps/glew/include
        deps/glfw/include
        include
)

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

link_libraries(
        sfml-system
        sfml-window
        sfml-graphics
        libglew_static
        glfw
        imgui-sfml
        dear_imgui
        )