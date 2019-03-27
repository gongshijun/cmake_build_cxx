## 工程主cmake文件详解

主要可以分为4块来理解。  
1. 工程通用配置  
2. kos_conf 文件配置
3. 项目源文件配置
4. 项目target设置

### 工程通用配置
主要完成工程名或者通用版本号，字符串，以及路径配置。

```c  

// 配置工程名，以及使用的语言
project(YUSUR-KOS-CMAKE LANGUAGES CXX)

// 配置最低需要cmake版本号
cmake_minimum_required (VERSION 3.14.0)

// 设置编译器参数，windows下VS是自动默认配置的，所以不需要配置
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 Wall -fPIC")
endif()

// 添加资源文件， easylogging需要的配置文件
set (SOURCE_DIR source)
configure_file (
    ${SOURCE_DIR}/conf/easylogging.conf 
    ${SOURCE_DIR}/conf/easylogging.conf 
    @COPY
)

// 添加include目录，因为最后生成 kos_conf.h 是放置在build目录下的
// 因此，也需要把build目录添加进去
// CMAKE_CURRENT_SOURCE_DIR 和 CMAKE_CURRENT_BINARY_DIR， 是cmake自动
// 生成的变量，分别对应当前cmake文件构建时的源文件目录和生成的二进制文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

```

### kos_conf 文件配置
`kos_conf.h` 主要用来支持通过cmake来配置，程序中需要使用可配置宏定义以及字符串、或者配置文件资源文件等。

```c
// 首先将option.txt引入，这样我们可以实现在cmake中，判断是否设置哪些宏
include (option.txt)

// 根据option.txt中，是否开启 KOS_DEBUG_ENABLE， 来决定是否需要使用日志系统
// 同时，根据操作系统来，来设置配置文件的路径
// 
/*  kos_conf.in.h 文件内容如下
// kos log configuration file
#cmakedefine KOS_LOG_CONF_FILE_PATH "@KOS_LOG_CONF_FILE_PATH@"
*/
// 如果下面的配置生效之后，cmake会自动替换上面 @KOS_LOG_CONF_FILE_PATH@ 字段
// 即变为 #define KOS_LOG_CONF_FILE_PATH "source\\conf\\kernel_config.xml"
if (KOS_DEBUG_ENABLE)
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

// configure_file 命令用来，完成文件对应映射， @ONLY表示，只替换@KOS_LOG_CONF_FILE_PATH@ 类似的变量
configure_file (
    conf/kos_conf.in.h
    conf/kos_conf.h 
    @ONLY
)

```

### 项目源文件配置

项目源文件配置，我们分为两种形式，一种为源文件构建，一种为OBJ构建。  

#### OBJ构建
OBJ构建，在主cmake中相对比较简单，

只需要使用`add_subdirectory (${subdir})`命令添加对应目录，以及在对应目录下面自行完成CMakeLists.txt就行了。

#### 源文件构建
源文件构建，在主cmake中就相对而言复杂一点，相当于把目录下面的cmake文件，也书写在主cmake文件中了。

为了自动化构建项目， 我们均采用cmake自动搜索目录和源文件的形式来完成构建。

主要用到一下宏命令和`file`文件命令  
```Bash
# 因为我是用vscode来进行编写，所以当前目录下面有.vscode文件，因此，
# 在搜索目录时需要将其去除。
# 除此之外，还除去了build目录、main（主程序）目录，utest（单元测试）目录。
# 后面两个目录，将在后面可选择进行
# auto list all directory, except build or utest or .* or main or source
# MACRO 程序，主要实现将curdir目录下，所有文件夹，放回给result
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

#############################################
# 下面这段脚本，主要是将当前目录下面的文件夹，通过 add_subdirectory 编译中来
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
#############################################

SUBDIRLIST_NOBUILD(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

#############################################
# 下面这段脚本，主要实现将每个目录下面的源文件找到，并添加到KOS_SRC_RESOURCE变量中
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
    # 通过source_group命令，可以在vs中建立虚拟目录
    # Create named folders for the sources within the .vcproj
    # Empty name lists them directly under the .vcproj
    source_group(${subdir} FILES ${src_resources})
endforeach()
#############################################
```

### 项目target设置

源文件构建比较简单，只需要将我们遍历得到的所有源文件添加到目标即可。  
OBJ构建，根据我们规则，每个目录生成的`obj`文件形式为 `目录名_obj`，因此需要做一下简单处理。

#### 源文件构建
只需要通过如下命令，就可以完成
```bash
add_executable (kos_utest  
    ${KOS_SRC_RESOURCE} 
    ${KOS_UTEST_SRC_RESOURCE}
)
```
#### OBJ构建
需要注意的是，引用OBJ库时，需要用 `$<TARGET_OBJECTS:obj_name>`这种形式。

```bash
# 首先根据我们的规则，获取所有的OBJ name， 然后添加到目标中
set (TARGET_OBJ "")
FOREACH(subdir ${SUBDIRS})
    list (APPEND TARGET_OBJ $<TARGET_OBJECTS:${subdir}_obj>)
ENDFOREACH()

list (APPEND TARGET_OBJ $<TARGET_OBJECTS:utest_obj>)
add_executable (kos_utest  
        ${TARGET_OBJ}
)
```
