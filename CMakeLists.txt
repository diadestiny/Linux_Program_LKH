cmake_minimum_required(VERSION 3.5.1)
project(Linux_Program_LKH)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread ")
add_executable(main_lkh main.cpp CLThread.cpp CLThread.h CLExecutive.h CLExecutiveFunctionProvider.h TableHelper.cpp TableHelper.h Record.h BPTree.h BPTree.cpp MyCLExecutiveFunction.h CLMutex.cpp CLMutex.h Record.h Record.cpp ThreadTest.cpp ThreadTest.h)