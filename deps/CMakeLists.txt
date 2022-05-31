# lager sfml targets
message(STATUS "Building SFML")
if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/SFML/.git" )
    message( SEND_ERROR "SFML submodule is empty. Please run
git submodule update --init --recursive"
            )
endif()
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

# imgui og imgui_sfml
message(STATUS "Building imgui-sfml")
if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/imgui/.git" )
    message( SEND_ERROR "imgui submodule is empty. Please run
git submodule update --init --recursive"
            )
endif()
if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/imgui/.git" )
        message( SEND_ERROR "imgui-sfml submodule is empty. Please run
git submodule update --init --recursive"
                )
endif()
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
add_subdirectory(imgui-sfml)
