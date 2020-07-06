<!--
 * @Description: Copyright(c) All rights reserved.
 * @Author: Shijun Gong
 * @Date: 2020-06-21 08:17:07
 * @LastEditors: Shijun Gong
 * @LastEditTime: 2020-06-21 09:57:39
--> 
# CMake build cxx based on target
## CMake Do's and Don'ts
参考：https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1
### CMake Antipatterns
1. 不要使用全局函数：如 ```link_directories, include_libraries```。
2. 不要使用不必要的PUBLIC要求：可以设置成PRIVATE。
3. 不要 GLOB 文件：Make 或者其他工具将不知道你增加了文件，除非你运行cmake。CMake 3.12增加了 ```CONFIGURE_DEFENDS```标志。
4. 直接link到构建文件：始终链接到target（如果有）。
5. 链接时不要跳过 PUBLIC/PRIVATE：这将导致整个将来的链接都缺少关键字。
### CMake Patterns
1. Treat CMake as code: It is code. It should be as clean and readable as all other code.
2. Think in targets: Your targets should represent concepts. Make an (IMPORTED) INTERFACE target for anything that should stay together and link to that.
3. Export your interface: You should be able to run from build or install.
4. Write a Config.cmake file: This is what a library author should do to support clients.
5. Make ALIAS targets to keep usage consistent: Using add_subdirectory and find_package should provide the same targets and namespaces.
6. Combine common functionality into clearly documented functions or macros: Functions are better usually.
7. Use lowercase function names: CMake functions and macros can be called lower or upper case. Always user lower case. Upper case is for variables.
8. Use cmake_policy and/or range of versions: Policies change for a reason. Only piecemeal set OLD policies if you have to.

## 要求
1. CMake应该自动找出传递依赖关系，并正确设置包含路径和连接器路径。

2. 将我们的源代码树组织到每个模块的目录中，每个模块带有CMakeLists。我们将使用父CMakeLists文件将所有模块绑定在一起，但是该顶层文件应该是可选的，并且仅在将所有必需的模块/依赖项纳入范围之内。

3. 区分库的公共头文件和私有头文件。我们将公共头文件放在一个```include```目录下面，并且每个独立的库对应一个文件夹。如```include/mylib```，同时将```include```加到我们的搜索路径中，使得引用头文件时用如此形式```<mylib/header.h>```。


