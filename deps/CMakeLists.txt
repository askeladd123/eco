## lager sfml targets
#message(STATUS "Building SFML")
#if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/SFML/.git" )
#    message( SEND_ERROR "SFML submodule is empty. Please run
#git submodule update --init --recursive"
#            )
#endif()

option(SEARCH_DEPS "Search system for dependencies before pulling from Git." ON)
set(SEARCH_DEPS ON)

find_package(Git QUIET)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "Couldn't find Git on your system.")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(FATAL_ERROR "The project has to be built as a Git repository.")
endif()

## SFML SFML SFML SFML
if (SEARCH_DEPS)
    message(STATUS "looking for SFML on your system")
    find_package(SFML QUIET COMPONENTS system window graphics)
    if(SFML_FOUND)
        message(STATUS "found SFML on your system")
    endif()
    if(NOT SFML_FOUND)
        message(STATUS "couldn't find SFML on your system")
    endif()
endif()

if (NOT SEARCH_DEPS OR NOT SFML_FOUND)
    message(STATUS "pulling SFML from Github")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive SFML
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SFML_RESULT)
    if (NOT GIT_SFML_RESULT EQUAL "0")
        message(FATAL_ERROR "failed to pull SFML from Github.")
    endif()
    message(STATUS "pulled SFML from Github")
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
endif()

# imgui og imgui_sfml
message(STATUS "pulling imgui from github")
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive imgui
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_imgui_RESULT)
if (NOT GIT_imgui_RESULT EQUAL "0")
    message(FATAL_ERROR "Failed to pull imgui from Github.")
endif()
message(STATUS "pulled imgui from github")

#if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/imgui/.git" )
#    message( SEND_ERROR "imgui submodule is empty. Please run
#git submodule update --init --recursive"
#            )
#endif()
#if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/imgui/.git" )
#        message( SEND_ERROR "imgui-sfml submodule is empty. Please run
#git submodule update --init --recursive"
#                )
#endif()

message(STATUS "pulling imgui-sfml from github")
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive imgui-sfml
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_imgui-sfml_RESULT)
if (NOT GIT_imgui-sfml_RESULT EQUAL "0")
    message(FATAL_ERROR "Failed to pull imgui-sfml from Github.")
endif()
message(STATUS "pulled imgui-sfml from github")

message(STATUS "Building imgui-sfml")
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
add_subdirectory(imgui-sfml)
