# cmake HowTo

## 概述

cmake可以用来生成项目工程文件，比如 Linux 下的 Makefile 等文件，VS下的 sln 等文件。cmake使用一个名为 CMakeLists.txt 的文件来描述项目构建过程。

使用 cmake 构建一个项目的流程如下：

1. 编写 CMakeLists.txt 文件

2. 执行`cmake <path>`生成工程文件，path目录下存放着CMakeLists.txt文件

3. 编译项目，比如 Linux 下可使用 make 命令

## 安装与使用

CentOS 7安装命令：

```shell
$ yum install cmake
```

Ubuntu18.04 安装命令：

```shell
$ sudo apt-get install cmake
```

Windows下直接下载安装包即可：https://cmake.org/download/

**构建项目**

下面以Linux平台为例。

使用方法为：

```shell
$ cmake path
$ make
```

使用path目录下的CMakeLists.txt来生成Makefile文件，生成的Makefile文件位于当前cmake命令执行目录。

cmake命令还会在命令执行目录生成一些中间文件。

**清理项目**

只需输入：

```shell
$ make clean
```

但不会清理cmake生成的中间文件。

**外部构建**

cmake除了会在命令执行目录生成MakeFile文件，还会生成许多一些中间文件，因此最好是把它们统一放到一个目录中，在此目录执行cmake，这就是外部构建。

例如，可在项目目录下创建一个build目录，作为cmake命令的执行目录，CMakeLists.txt文件放在项目目录下，然后这样构建项目：

```
$ cd build
$ cmake ..
$ make
```

这样，想要删除cmake生成的中间文件时，直接执行`rm -rf build`即可。

也可以这样执行外部构建：

```
$ cmake -H. -Bbuild
```

-H. 表示在当前目录寻找 root CMakeLists.txt 。

-Bbuild 表示将 cmakefiles 创建到 build 目录， build 目录也可以自动创建。

**生成Debug或Release版本的程序**

```
$ cmake -DCMAKE_BUILD_TYPE=Debug path
```

这里设置了变量CMAKE_BUILD_TYPE的值为Debug，表示生成的是Debug版本的程序。还可以取值为Release。

## 编写CMakeLists.txt

#### 一些语法

CMakeLists.txt语法由指令、变量、注释组成。

**指令**

指令由指令名、小括号、参数组成。参数以空格分隔。

指令可以不分大小写。

**变量**

变量分为内置的和自定义的。

引用变量的方法是：${变量名}。

变量是全局的，在上层CMakeLists.txt定义的变量，在下层可以使用。

**注释**

`##`符号后面的内容被认为是注释

**条件**

使用 if else endif 来进行条件选择.

例子:

```cmake
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(STATUS "Configure on/for Linux")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	message(STATUS "Configure on/for macOS")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Configure on/for Windows")
else ()
	message(STATUS "Configure on/for %{CMAKE_SYSTEM_NAME}")
endif()
```

or:

```cmake
if (MSVC)
	...
else ()
	...
endif (MSVC)
```

#### 一些指令

在官方文档中，指令中尖括号的内容是必填项，而方括号的内容是选填项，其余的是固定内容。

**CMAKE_MINIMUM_REQUIRED**

限定cmake的版本，如果当前cmake版本低，则生成失败。通常它位于顶层CMakeLists.txt的第一行。

使用例子：

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
```

**PROJECT**

定义项目的名称。

使用例子：

```cmake
PROJECT(projectname)
```

对于 vs ，这样的指令使得 sln 文件的名字为 projectname 。

**MESSAGE**

发送一段信息文本到标准输出。

使用例子：

```cmake
MESSAGE("cmake start")
```

**SET**

自定义一个变量，或者改变内置变量的值。

指令语法：

```cmake
SET(VAR [VALUE])
```

使用例子：

```cmake
SET(SRC_LIST main.c t1.c t2.c)
```

**INCLUDE_DIRECTORIES**

设置头文件包含目录。

使用例子：

```cmake
INCLUDE_DIRECTORIES(. ./src) ## 目录列表
```

**ADD_SUBDIRECTORY**

指明本工程中还有一个子目录，当执行到此指令时，会进入到子目录中，使用子目录中的CMakeList进行构建。

使用例子：

```cmake
ADD_SUBDIRECTORY(sub_project_dir)
```

**FILE**

文件相关的操作。支持通配符扩展。

使用例子：

```cmake
FILE(GLOB_RECURSE SRC_FILES *.cpp *.h) ## 获取当前处理的CMakeLists.txt文件所在目录及其子目录中所有的cpp文件和h文件，放到SRC_FILES变量里
```

GLOB_RECURSE代表全局递归查找。

**ADD_EXECUTABLE**

设置生成一个可执行文件。通常位于次级CMakeLists.txt。

指令语法：

```cmake
ADD_EXECUTABLE(exefile src_file_list)
```

使用例子：

```cmake
ADD_EXECUTABLE(main main.c t1.c t2.c)
```

**ADD_LIBRARY**

设置生成一个库文件。

指令语法：

```cmake
ADD_LIBRARY(libname [SHARED | STATIC] source_list)
```

说明：

- libname无需加lib前缀和.so后缀
- SHARED表示动态库，STATIC表示静态库，默认是静态库

**LINK_DIRECTORIES和TARGET_LINK_LIBRARIES**

设置链接库的所在目录，设置目标所需要的链接库文件。

指令语法：

```cmake
LINK_DIRECTORIES(dir_list)
TARGET_LINK_LIBRARIES(target lib_list)
```

注：

- 如果是共享库，可以不写前缀与后缀；如果是静态库，要写全名

- TARGET_LINK_LIBRARIES命令要写在ADD_EXECUTABLE后面

**STRING**

可以修改字符串，将其存到一个变量里。此变量可以事先没有SET。

指令语法：

```cmake
STRING([TOLOWER | TOUPPER] string output_val) ## 将string转换成小写，赋给output_val
```

使用例子：

```cmake
STRING(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
```

**source_group**

可以在 vs 中设置筛选器，里面包含指定的项目文件。

指令语法：

```cmake
source_group(<name> [FILES <src>...] [REGULAR_EXPRESSION <regex>])
source_group(TREE <root> [PREFIX <prefix>] [FILES <src>...])
```

使用例子：

```cmake
source_group(src FILES ${SRC_FILES}) # src 是筛选器的名字
```

PS: 在vs2015下面经过测试发现，需要重新构建项目，这个指令才会生效。

**set_property**

在一个作用域内设置某属性的值。

指令语法：

```cmake
set_property(<GLOBAL                            |
              DIRECTORY [dir]                   |
              TARGET    [target1 [target2 ...]] |
              SOURCE    [src1 [src2 ...]]       |
              INSTALL   [file1 [file2 ...]]     |
              TEST      [test1 [test2 ...]]     |
              CACHE     [entry1 [entry2 ...]]>
             [APPEND] [APPEND_STRING]
             PROPERTY <name> [value1 [value2 ...]])
```

使用例子：

```cmake
set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "project" ) # 设置 vs 启动项目为 project
```

DIRECTORY 默认使用当前的目录为作用域。

**add_custom_command**

设置一些自定义的命令。

例如，在生成前和生成后执行以下命令行的命令：

```cmake
# 生成前：更新一下 compileversion.cpp 文件，生成一个新的编译版本号
add_custom_command(TARGET EXEgameworld_${ARPG_BUILD_TYPE}
	PRE_BUILD
	COMMAND echo [PRE_BUILD] Update compileversion for gameworld
	COMMAND copy /B compileversion.cpp +,, > nul
	COMMENT "Update compileversion"
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/gameworld
)

# 生成完：将 EXEgameworld 拷贝到给 check_config
add_custom_command(TARGET EXEgameworld_${ARPG_BUILD_TYPE}
	POST_BUILD
	COMMAND echo [POST_BUILD] copy EXEgameworld for check_config
	COMMAND copy vsproject\\Debug\\EXEgameworld_debug.exe config\\server_opera_tools\\bin
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
)
```

#### 一些内置变量

**PROJECT_BINARY_DIR与PROJECT_SOURCE_DIR**

PROJECT_BINARY_DIR默认值是编译（make）发生的目录。

PROJECT_SOURCE_DIR是工程的顶层目录（顶层CMakeLists.txt所在目录）。

**EXECUTABLE_OUTPUT_PATH与LIBRARY_OUTPUT_PATH**

最终的目标二进制位置；最终的共享库位置。都不包含中间文件。

通常用SET命令设置，如：

```shell
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
```

**CMAKE_CXX_FLAGS**

C++编译选项。

另外还有：

- CMAKE_CXX_FLAGS, 默认选项
- CMAKE_CXX_FLAGS_DEBUG，当CMAKE_BUILD_TYPE为Debug时启用
- CMAKE_CXX_FLAGS_RELEASE，当CMAKE_BUILD_TYPE为Release时启用

**CMAKE_CURRENT_SOURCE_DIR**

当前处理的CMakeLists.txt所在路径。

## 几个例子

### 单项目工程

```bash
# 要求 cmake 最低版本
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# 设置工程名
project(project_name)

# 自定义变量
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LINK_DIR ${PROJECT_SOURCE_DIR}/lib)
set(LIBS m)

# 设定编译选项
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -std=c++11 -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-g -Wall -std=c++11")

# 设定头文件包含目录
include_directories(${INCLUDE_DIR})

# 设定链接目录
link_directories(${LINK_DIR})

# 设定项目文件
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h")

# 设定输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out)

# 设定可执行程序及生成它依赖的文件
add_executable(project_name ${SRC_FILES})

# 设定可执行程序依赖的库
target_link_libraries(project_name ${LIBS})
```

### 多项目工程

#### 顶层 CMakeLists

```bash
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# 设置工程名
project(project_name)

# 自定义变量
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LINK_DIR ${PROJECT_SOURCE_DIR}/lib)
set(LIBS m)

# 设置编译选项
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -std=c++11 -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-g -Wall -std=c++11")

# 设定头文件包含目录
include_directories(${INCLUDE_DIR})

# 设定链接目录
link_directories(${LINK_DIR})

# 设定输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out)

# 引入子项目
add_subdirectory(program)
```

#### 子项目 CMakeLists

```bash
# 自定义变量
set(PROGRAM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 设定头文件包含目录
include_directories(${INCLUDE_DIR} ${PROGRAM_INCLUDE_DIR})

# 设定项目文件
file(GLOB_RECURSE SRC_FILES "*.cpp" "*.h")

# 设置可执行程序依赖的文件
add_executable(program_${CMAKE_BUILD_TYPE} ${SRC_FILES})

# 设置可执行程序依赖的库
target_link_libraries(program_${CMAKE_BUILD_TYPE} ${LIBS})
```

### 一个采取外部构建的脚本

```shell
#! /bin/bash

# usage: $ sh build.sh [rebuild | clear]

clear()
{
	if [ ! -d tmp_build ]; then
		return
	fi

	cd tmp_build
	make clean
	cd ..
	rm -rf tmp_build
}

if [ "$1" = "rebuild" ]; then
	clear
elif [ "$1" = "clear" ]; then
	clear
	exit
fi

mkdir -p tmp_build
cd tmp_build

cmake -DCMAKE_BUILD_TYPE=debug ..
time make -j4
```

## 参考资料

[在 linux 下使用 CMake 构建应用程序](https://www.ibm.com/developerworks/cn/linux/l-cn-cmake/index.html)

[官方网站](https://cmake.org)