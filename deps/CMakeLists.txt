
option(DEPS_FIND "Search system for dependencies before pulling from Git." ON)

find_package(Git QUIET)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "couldn't find Git on your system")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(FATAL_ERROR "the project has to be built as a Git repository")
endif()

## SFML SFML SFML SFML
if (DEPS_FIND)
    message(STATUS "looking for SFML on your system")
    find_package(SFML QUIET COMPONENTS system window graphics)
    if(SFML_FOUND)
        message(STATUS "found SFML on your system")
    endif()
    if(NOT SFML_FOUND)
        message(STATUS "couldn't find SFML on your system")
    endif()
endif()

if (NOT DEPS_FIND OR NOT SFML_FOUND)
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SFML/.git" )
        message(STATUS "pulling SFML from Github")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init SFML
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SFML_RESULT)
        if (NOT GIT_SFML_RESULT EQUAL "0")
            message(FATAL_ERROR "failed to pull SFML from Github")
        endif()
    endif()
    message(STATUS "building SFML")
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
    message(STATUS "built SFML")
endif()

# imgui og imgui_sfml
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui/.git" )
    message(STATUS "pulling imgui from github")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive imgui
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_imgui_RESULT)
    if (NOT GIT_imgui_RESULT EQUAL "0")
        message(FATAL_ERROR "Failed to pull imgui from Github.")
    endif()
    message(STATUS "pulled imgui from github")
endif()

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui-sfml/.git" )
    message(STATUS "pulling imgui-sfml from github")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive imgui-sfml
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_imgui-sfml_RESULT)
    if (NOT GIT_imgui-sfml_RESULT EQUAL "0")
        message(FATAL_ERROR "failed to pull imgui-sfml from Github.")
    endif()
    message(STATUS "pulled imgui-sfml from github")
endif()

message(STATUS "building imgui-sfml")
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)
if (SFML_FOUND)
    set(IMGUI_SFML_FIND_SFML ON)
else()
    set(IMGUI_SFML_FIND_SFML OFF)
endif()
set(IMGUI_SFML_IMGUI_DEMO ON)
add_subdirectory(imgui-sfml)
message(STATUS "built imgui-sfml")

# ask libs
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ask_libs/.git" )
    message(STATUS "pulling ask_libs from github")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive ask_libs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_ask_libs_RESULT)
    if (NOT GIT_ask_libs_RESULT EQUAL "0")
        message(FATAL_ERROR "failed to pull ask_libs from Github.")
    endif()
    message(STATUS "pulled ask_libs from github")
endif()

set(dep_targets sfml-system sfml-window sfml-graphics ImGui-SFML PARENT_SCOPE)
set(dep_includes deps/imgui-sfml deps/imgui deps/ask_libs/include PARENT_SCOPE)#dette funker ikke hvis du flytter på mappen
if (NOT SFML_FOUND)
    list(APPEND dep_includes deps/SFML/include)
endif()

