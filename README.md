# Project_StateMachine
This is project for the design and use of statemachine
一 本开源共享项目是对软件系统中常用的状态机的设计和实现，主要包含以下几部分内容：
1）通过文档《状态机设计》对状态机进行了简单介绍，介绍了状态机的概念、设计和调度方法。
2）通过编码实现了一个状态机类。
3）对状态机类进行实例化，完成了对状态机的调度演示。

二 环境和工程介绍
本项目是在Linux（Ubuntu 16.04)终端下编写的C++程序，代码编辑器为vim，编译工具为CMake。
在CMakeLists.txt中指定工程名称为Myshare_StateMachine，头文件为目录为include，源文件目录为src。include目录下包含StateMachine.h和StateInfo.h两个头文件，src目录下包含Statemachine.cpp、StateInfo.cpp和Scheduler.cpp三个源文件。其中StateMachine.h和Statemachine.cpp是对状态机类的实现；StateInfo.h和StateInfo.cpp是为了调度演示如何调度状态机而设计的配套文件；Scheduler.cpp是对状态机的调度文件，是main函数所在的源文件。所有头文件和源文件均有较为详细的注释，若有疑问，欢迎随时联系本人进行交流。

编译方法：
    1）进入Linux终端，输入cd 切换至Myshare_StateMachine/build目录；
    2）输入cmake ..，进行工程信息配置（注意cmake和点之间有一个空行）；
    3）输入make，进行编译和链接；
    4）输入./Myshare_StateMachine运行编译结果；



