cmake_minimum_required (VERSION 3.15.0)

### Update all git submodules
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

### Require out-of=source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" 
    LOC_PATH)

if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build 
    in a source directory 
    (or any directory with a CMakeLists.txt file). 
    Please make a build subdirectory. 
    Feel free to remove CMakeCache.txt 
    and CMakeFiles.")
endif()

project(PRO_TARGET LANGUAGES CXX)

include (option.txt)

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    @ONLY
)

### Update submodules as needed
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} 
        submodule update --init --recursive 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message (FATAL_ERROR "git submodule 
            update --init failed with ${GIT_SUBMOD_RESULT}, 
            please chechout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/repo/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()