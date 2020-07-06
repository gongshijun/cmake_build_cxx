<!--
 * @Description: Copyright(c) All rights reserved.
 * @Author: Shijun Gong
 * @Date: 2020-06-21 07:39:53
 * @LastEditors: Shijun Gong
 * @LastEditTime: 2020-06-21 07:51:29
--> 
# CMAKE BUILD CXX
CMake是管理C ++系统构建的好​​工具。它构建迅速，支持主要用例，并且非常灵活。问题是，它太灵活了，对于习惯于自己编写Makefile的人们来说，并不总是很明显应该使用什么CMake命令和属性。如果习惯于仅将一些编译器标志放入CXX_FLAGS环境变量中，即使它支持更好的管理构建方式，您也可能会在CMake中这样做。

本项目记录本人学习CMAKE的一些经验，目前总共分配两个工程：

```cmake_makefile``` 类似于Makefile文件编写式风格，导致自己的项目很难移植，也不方便在不同的上下文中重用，但是限于本人一开始喜欢在vs中开发调试代码，因此该项目可能非常适合开发初期且喜欢用vs调试的开发人员。

```cmake_target``` 再经过一段时间学习之后，特别是看了大公司的开源代码，感觉之前的项目是在存在很多缺陷，如不支持自动安装库（需要手动拷贝头文件），以及不支持```find_package```等现代cmake式的命令（影响库移植）等等。因此，该项目将记录如何基于cmake的target来编程实现build cxx系统来方便的完成开发等。

主要参考：

https://rix0r.nl/blog/2015/08/13/cmake-guide/

https://cliutils.gitlab.io/modern-cmake/

# 详细介绍
在每个项目项目下面，都有详细的文档介绍，可以自行参考。
