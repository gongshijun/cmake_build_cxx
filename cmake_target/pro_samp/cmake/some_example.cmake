### set C++ standards
## Global properties
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

## Based on target
#set_target_properties(
#    myTarget PROPERTIES
#    CXX_STANDARD 11
#    CXX_STANDARD_REQUIRED YES
#    CXX_EXTENSIONS NO
#)
#Which is better, but still doesn't 
#have the sort of explicit control 
#that compiler features have for 
#populating PRIVATE and INTERFACE properties.

### Position independent code
#This is best known as the -fPIC flag. 
#Much of the time, 
#you don't need to do anything. 
#CMake will include the flag for 
#SHARED or MODULE libraries. 
#If you do explicitly need it:

## do it globally
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
## to explicitly turn it ON (or OFF) for a target.
set_target_properties(lib1 PROPERTIES 
    POSITION_INDEPENDENT_CODE ON)


### Download repo
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.9.1
)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
    macro(FetchContent_MakeAvailable NAME)
        FetchContent_GetProperties(${NAME})
        if(NOT ${NAME}_POPULATED)
            FetchContent_Populate(${NAME})
            add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
        endif()
    endmacro()
endif()

# CMake 3.14+
FetchContent_MakeAvailable(catch)
