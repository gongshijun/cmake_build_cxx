## 目录cmake详解

### 第一步
获取当前目录名，生成 name_obj 目标名

```bash
string (REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGET ${CURRENT_FOLDER}_obj)
```

### 第二步
可以根据需要，是否添加当前目录到include中，然后搜索所有源文件

```bash
include_directories (.)

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

# 通过source_group 可以在vs中建立虚拟目录
source_group(${CURRENT_FOLDER} FILES ${MAIN_SOURCES})
```

### 第三步
最后生成构建目标

```bash
add_library(${TARGET} OBJECT 
    ${ALL_SRC_RESOURCE}
)
```