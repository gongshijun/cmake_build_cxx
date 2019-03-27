# cmake_build_cxx
这个项目，主要记录本人这四天来学习cmake构建系统的经历
### using cmake build a big project. The project contain nultilevel directory and resource files. This project contain two ways to build project. One, build all project from sources. Two, build all project from objects. if there is any mistake, please give me your advice.  

#### 项目需求：
一个大型工程，工程需要包括多级目录结构，需要有主程序以及单元测试，以及一些资源文件用来进行项目配置。除此之外，单元测试和主程序之间，构成可选项。也就是说，要么进行单元测试，要么运行主程序。 另外，处于个人爱好，比较喜欢在vs中开发代码，因此需要在vs显示的构建虚拟工程目录。  
#### 需要说明的一点：
由于大型工程，不同目录之间存在相互引用，以及引用顺序不方便确认的情况，因此，本工程提供了两种构建方式。第一，源文件构建，将所有源文件，放在一起进行构建，这样可以方便在vs一个工程中，进行查看与调试。第二， 目标文件构建，先将不同目录下的源文件，生成对应的目标文件，再进行构建。

#### 项目效果如下图
配置： 可以通过设置下面两个参数来选择，是构建单元测试，还是主程序，以及采用object方式，还是源程序。  
配置选项，在根目录`option.txt`文件中  
`option (UNIT_TEST_ENABLE "Enable KOS unit test" OFF)`  
`option (OBJECT_BUILD_ENABLE "Enable build from object" OFF)`  

主程序，使用源文件构建，效果如下图：  

![main src] (./images/main_src.png)

