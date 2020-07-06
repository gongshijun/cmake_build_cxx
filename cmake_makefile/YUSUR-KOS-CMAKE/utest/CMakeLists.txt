string (REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGET ${CURRENT_FOLDER}_obj)

MESSAGE(STATUS "cmake curdir: " ${CURRENT_FOLDER})

# The recommended way to collect sources in variable 
# COMMON_SOURCES by explicitly specifying the source files
# set  (COMMON_SOURCES 
#    "common/kos_uuid_utest.cpp"
#)

#set (UTEST_SOURCES 
#    "test.h" 
#    "testmain.cpp"
#)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
# source_group("" FILES ${UTEST_SOURCES})
# source_group("common" FILES ${COMMON_SOURCES})

# Properties->C/C++->General->Additional Include Directories
include_directories (.)

# set (SRC_UTEST 
#    ${UTEST_SOURCES}
#    ${COMMON_SOURCES}
#)

# auto list all directory, except build or utest or .* or main
MACRO(SUBDIRLIST_NOBUILD result curdir)
    FILE(GLOB children RELATIVE ${curdir} CONFIGURE_DEPENDS ${curdir}/*)
    SET(dirlist "")
    # MESSAGE(STATUS "utest resource: " ${children})
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            if((NOT (${child} MATCHES "build")) AND (NOT (${child} MATCHES utest))
                AND (NOT (${child} MATCHES .vscode)) 
                AND (NOT (${child} MATCHES main)))
                LIST(APPEND dirlist ${child})
            ENDIF()
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

#### obtain src resource ####
SUBDIRLIST_NOBUILD(SUBDIRS_ ${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB MAIN_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    ./*.h
    ./*.cpp
)
source_group(${CURRENT_FOLDER} FILES ${MAIN_SOURCES})

MESSAGE(STATUS "utest resource: " ${MAIN_SOURCES})

# all resources
set (ALL_SRC_RESOURCE ${MAIN_SOURCES})

FOREACH(subdir ${SUBDIRS_})
    # set(src_resource "utest_${subdir}_resources")
    FILE(GLOB src_resource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
        ./${subdir}/*.h
        ./${subdir}/*.cpp
    )
    #set
    MESSAGE(STATUS "utest resource: " ${src_resource})
    list (APPEND ALL_SRC_RESOURCE ${src_resource})
    # set (sub_path, "utest\\\\${subdir}")
    source_group(${CURRENT_FOLDER}\\${subdir} FILES ${src_resource})
ENDFOREACH()

add_library(${TARGET} OBJECT 
    ${ALL_SRC_RESOURCE}
)
