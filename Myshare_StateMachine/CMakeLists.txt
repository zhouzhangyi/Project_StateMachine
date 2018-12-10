#1.cmake version,指定cmake版本
cmake_minimum_required(VERSION 2.8)

#2.project name,指定项目的名称
PROJECT(Myshare_StateMachine)

#3.head file，头文件目录
INCLUDE_DIRECTORIES(include)

#4.source directory,源文件目录
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#5.set environment varible,设置环境变量
SET(MY_NAME ${DIR_SRCS})

#6.add executable file
ADD_EXECUTABLE(${PROJECT_NAME} ${MY_NAME})

#7.add link library,添加可执行文件所需的库
