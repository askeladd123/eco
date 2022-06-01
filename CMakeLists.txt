cmake_minimum_required(VERSION 3.21)
project(eco)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "Building project dependencies")
add_subdirectory(deps)

add_executable(eco
        src/main.cpp
        src/blob/logic.h
        src/blob/brain.h
        src/blob/graphics.h
        src/world.h
        src/blob/blob.h
        deps/ask_libs/include/ask/collision.h
        src/global_var.h
        )

target_include_directories(eco PRIVATE
        deps/SFML/include
        deps/imgui-sfml
        deps/imgui
        deps/ask_libs/include
        src
        )

target_link_libraries(eco PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        ImGui-SFML
        )

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})