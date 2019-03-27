project(YUSUR-KOS-CMAKE LANGUAGES CXX)

cmake_minimum_required (VERSION 3.14.0)

# KOS version and right
set (KOS_VERSION_MAJOR 1)
set (KOS_VERSION_MINOR 2)
set (KOS_VERSION_PATCH 3)
set (KOS_RIGHT_STR "ALL RIGHT RESERVED BY YUSUR")

# c++ compile options
# set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -fPIC")
# set(CMAKE_CXX_FLAGS "-std=c++11")
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 Wall -fPIC")
endif()

# add compile option
# if (MSVC)
    # warning level 4 and all warnings as errors
#    add_compile_options(/W4 /WX)
# else()
    # lots of warnings and all warnings as errors
#    add_compile_options(-Wall -Wextra -pedantic -Werror)
#endif()

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# add resource file
set (SOURCE_DIR source)
configure_file (
    ${SOURCE_DIR}/conf/easylogging.conf 
    ${SOURCE_DIR}/conf/easylogging.conf 
    @ONLY
)
configure_file (
    ${SOURCE_DIR}/conf/hd_doc.xml 
    ${SOURCE_DIR}/conf/hd_doc.xml 
    @ONLY
)
configure_file (
    ${SOURCE_DIR}/conf/inst_data_conf.xml 
    ${SOURCE_DIR}/conf/inst_data_conf.xml 
    @ONLY
)
configure_file (
    ${SOURCE_DIR}/conf/kernel_config.xml 
    ${SOURCE_DIR}/conf/kernel_config.xml 
    @ONLY
)

# include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#####################################################
#### configure kos_conf.h ####
include (option.txt)

if (KOS_DEBUG_ENABLE)
# add kos log system configure file
    if (WIN32)
        set (KOS_LOG_CONF_FILE_PATH "${SOURCE_DIR}\\\\conf\\\\easylogging.conf")
    else ()
        set (KOS_LOG_CONF_FILE_PATH "${SOURCE_DIR}/conf/easylogging.conf")
    endif()
endif ()

if (WIN32)
    set (YCC_KERNEL_CONF_PATH "${SOURCE_DIR}\\\\conf\\\\kernel_config.xml")
else ()
    set (YCC_KERNEL_CONF_PATH "${SOURCE_DIR}/conf/kernel_config.xml")
endif()

configure_file (
    conf/kos_conf.in.h
    conf/kos_conf.h 
    @ONLY
)
#####################################################

#####################################################
#### configure kos resource files ####

# auto list all directory, except build or utest or .* or main or source
MACRO(SUBDIRLIST_NOBUILD result curdir)
    FILE(GLOB children RELATIVE ${curdir} CONFIGURE_DEPENDS ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            if((NOT (${child} MATCHES "build")) AND (NOT (${child} MATCHES utest))
                AND (NOT (${child} MATCHES .vscode)) 
                AND (NOT (${child} MATCHES main)) 
                AND (NOT (${child} MATCHES source))
            )
                LIST(APPEND dirlist ${child})
            ENDIF()
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

if (OBJECT_BUILD_ENABLE)
    #### obtain all directory in CMAKE_CURRENT_SOURCE_DIR ####
    SUBDIRLIST_NOBUILD(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
    
    # MESSAGE(STATUS "OBJECT_BUILD_ENABLE resource: " ${SUBDIRS})
    FOREACH(subdir ${SUBDIRS})
        add_subdirectory (${subdir})
    ENDFOREACH()

    if (UNIT_TEST_ENABLE)
        add_subdirectory (utest)
    else ()
        add_subdirectory (main)
    endif ()
    
else (OBJECT_BUILD_ENABLE)
# The recommended way to collect sources in variable 
# COMMON_SOURCES by explicitly specifying the source files
#set (COMMON_SOURCES 
#    "common/uuid.cpp" 
#    "common/uuid.h"
#)
#MESSAGE(STATUS "common resource: " ${COMMON_SOURCES})

# The recommended way to collect sources in variable 
# utest by explicitly specifying the source files
#set (UTEST_COMMON_SOURCES 
#    "utest/common/kos_uuid_utest.cpp"
#)
#MESSAGE(STATUS "utest common resource: " ${UTEST_COMMON_SOURCES})

#set (UTEST_SOURCES 
#    "utest/test.h" 
#    "utest/testmain.cpp"
#)
#MESSAGE(STATUS "utest resource: " ${UTEST_SOURCES})

#set (SRC_UTEST 
#    ${UTEST_SOURCES}
#    ${UTEST_COMMON_SOURCES}
#)

# include_directories (${CMAKE_CURRENT_SOURCE_DIR}/utest)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
# source_group("common" FILES ${COMMON_SOURCES})
# source_group("utest" FILES ${UTEST_SOURCES})
# source_group(TREE utest PREFIX utest\\common ${UTEST_COMMON_SOURCES} )
# source_group("utest\\common" FILES ${UTEST_COMMON_SOURCES})

#### obtain all directory in CMAKE_CURRENT_SOURCE_DIR ####
SUBDIRLIST_NOBUILD(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# kos all resources
set (KOS_SRC_RESOURCE "")

# MESSAGE(STATUS "SUBDIRS resource: " ${SUBDIRS})
foreach(subdir ${SUBDIRS})
    # set(src_resource " ")
    FILE(GLOB src_resources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
        CONFIGURE_DEPENDS 
        ${subdir}/*.h
        ${subdir}/*.cpp
    )
    # MESSAGE(STATUS "src_resource resource: " ${src_resources})
    list (APPEND KOS_SRC_RESOURCE ${src_resources})
    source_group(${subdir} FILES ${src_resources})
endforeach()

if (UNIT_TEST_ENABLE)
    #### obtain utest src resource ####
    SUBDIRLIST_NOBUILD(SUBDIRS_UTEST ${CMAKE_CURRENT_SOURCE_DIR}/utest)

    include_directories (${CMAKE_CURRENT_SOURCE_DIR}/utest)

    set (UTEST_SOURCES 
        "utest/test.h" 
        "utest/testmain.cpp"
    )
    source_group("utest" FILES ${UTEST_SOURCES})

    # utest all resources
    set (KOS_UTEST_SRC_RESOURCE ${UTEST_SOURCES})

    FOREACH(subdir ${SUBDIRS_UTEST})
        # set(src_resource "utest_${subdir}_resources")
        FILE(GLOB src_resource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
            utest/${subdir}/*.h
            utest/${subdir}/*.cpp
        )
        #set
        # MESSAGE(STATUS "utest resource: " ${src_resource})
        list (APPEND KOS_UTEST_SRC_RESOURCE ${src_resource})
        # set (sub_path, "utest\\\\${subdir}")
        source_group(utest\\${subdir} FILES ${src_resource})
    ENDFOREACH()
    # MESSAGE(STATUS "utest common resource: " ${KOS_UTEST_SRC_RESOURCE})
else ()
    #### obtain main src resource ####
    SUBDIRLIST_NOBUILD(SUBDIRS_UTEST ${CMAKE_CURRENT_SOURCE_DIR}/main)

    # include_directories (${CMAKE_CURRENT_SOURCE_DIR}/utest)

    FILE(GLOB MAIN_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
        main/*.h
        main/*.cpp
    )
    
    source_group("main" FILES ${MAIN_SOURCES})

    # main all resources
    set (KOS_MAIN_SRC_RESOURCE ${MAIN_SOURCES})

    FOREACH(subdir ${SUBDIRS_UTEST})
        # set(src_resource "utest_${subdir}_resources")
        FILE(GLOB src_resource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
            main/${subdir}/*.h
            main/${subdir}/*.cpp
        )
        # set
        # MESSAGE(STATUS "utest resource: " ${src_resource})
        list (APPEND KOS_MAIN_SRC_RESOURCE ${src_resource})
        # set (sub_path, "utest\\\\${subdir}")
        source_group(main\\${subdir} FILES ${src_resource})
    ENDFOREACH()
    # MESSAGE(STATUS "utest common resource: " ${KOS_UTEST_SRC_RESOURCE})
endif ()
#####################################################
endif(OBJECT_BUILD_ENABLE) 


#####################################################
#### configure kos targets ####
if (NOT OBJECT_BUILD_ENABLE)
    if (UNIT_TEST_ENABLE)
        add_executable (kos_utest  
            ${KOS_SRC_RESOURCE} 
            ${KOS_UTEST_SRC_RESOURCE}
        )
    else ()
        add_executable (kos_main  
            ${KOS_SRC_RESOURCE} 
            ${KOS_MAIN_SRC_RESOURCE}
        )
    endif ()
else ()
    set (TARGET_OBJ "")
    FOREACH(subdir ${SUBDIRS})
        list (APPEND TARGET_OBJ $<TARGET_OBJECTS:${subdir}_obj>)
    ENDFOREACH()

    if (UNIT_TEST_ENABLE)
        list (APPEND TARGET_OBJ $<TARGET_OBJECTS:utest_obj>)
    else ()
        list (APPEND TARGET_OBJ $<TARGET_OBJECTS:main_obj>)
    endif ()

    add_executable (kos_utest  
        ${TARGET_OBJ} 
    )
# $<TARGET_OBJECTS:utest_obj> 
# $<TARGET_OBJECTS:common_obj> 
endif ()
#####################################################