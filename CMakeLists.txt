cmake_minimum_required(VERSION 3.21)
project(eco)

set(CMAKE_CXX_STANDARD 20)

if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    MESSAGE(WARNING "project not tested with your compiler, only MinGW")
endif()

set(DEPS_FIND ON)
message(STATUS "building project dependencies")
add_subdirectory(deps)
message(STATUS "built project dependencies")

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

target_include_directories(eco PRIVATE ${dep_includes} src)

target_link_libraries(eco PUBLIC ${dep_targets})

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})