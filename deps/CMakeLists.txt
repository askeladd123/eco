message(STATUS "Building dependencies")

## deps
#set(glew-cmake_BUILD_SHARED OFF)
#add_subdirectory(glew)
#
##
#set(BUILD_SHARED_LIBS OFF)
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#add_subdirectory(glfw)

## lager imgui targets
#add_library(dear_imgui
#        imgui/imgui.cpp
#        imgui/imgui_draw.cpp
#        imgui/imgui_tables.cpp
#        imgui/imgui_widgets.cpp
#        imgui/imgui_demo.cpp
#        imgui/backends/imgui_impl_glfw.cpp
#        imgui/backends/imgui_impl_opengl3.cpp
#        )

# lager sfml targets
set(BUILD_SHARED_LIBS FALSE)# "TRUE to build SFML as shared libraries, FALSE to build it as static libraries")
set(SFML_BUILD_EXAMPLES FALSE)# "TRUE to build the SFML examples, FALSE to ignore them")
set(SFML_BUILD_WINDOW TRUE)# "TRUE to build SFML's Window module. This setting is ignored, if the graphics module is built.")
set(SFML_BUILD_GRAPHICS TRUE)# "TRUE to build SFML's Graphics module.")
set(SFML_BUILD_AUDIO FALSE)# "TRUE to build SFML's Audio module.")
set(SFML_BUILD_NETWORK FALSE)# "TRUE to build SFML's Network module.")
set(SFML_BUILD_DOC FALSE)# "TRUE to generate the API documentation, FALSE to ignore it")
set(SFML_BUILD_TEST_SUITE FALSE)# "TRUE to build the SFML test suite, FALSE to ignore it")
set(SFML_ENABLE_COVERAGE FALSE)# "TRUE to enable coverage reporting, FALSE to ignore it")
set(SFML_USE_SYSTEM_DEPS FALSE)# "TRUE to use system dependencies, FALSE to use the bundled ones.")
set(SFML_USE_STATIC_STD_LIBS FALSE)# "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")
add_subdirectory(SFML)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
add_subdirectory(imgui-sfml)
