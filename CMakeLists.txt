cmake_minimum_required(VERSION 3.21)
project(eco)

set(CMAKE_CXX_STANDARD 20)

if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    MESSAGE(WARNING "project not tested with your compiler, only MinGW")
endif()

message(STATUS "building project dependencies")
add_subdirectory(deps)

add_executable(eco
        src/main.cpp
        src/blob/logic.h
        src/blob/brain.h
        src/blob/graphics.h
        src/world.h
        src/blob/blob.h
        deps/ask_libs/include/ask/physics.h
        src/global_var.h
        )

target_include_directories(eco PRIVATE
        deps/SFML/include
        deps/imgui-sfml
        deps/imgui
        deps/ask_libs/include
#        ${SFML_INCLUDE_DIR}
        src
        )

target_link_libraries(eco PUBLIC
        sfml-system
        sfml-window
        sfml-graphics
        ImGui-SFML
#        ${SFML_LIBRARIES}
#        ${SFML_DEPENDENCIES}
        )

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})