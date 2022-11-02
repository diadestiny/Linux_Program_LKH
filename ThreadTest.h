//
// Created by linkaihao on 2022/10/26.
//

#ifndef THREADTEST_H
#define THREADTEST_H

#include <pthread.h>
#include <vector>
#include "Record.h"
#include "BPTree.h"
#include "CLMutex.h"
#include "TableHelper.h"


class ThreadTest {
public:

    // 测试线程-随机生成表格
    static void threadGenerateTest(int64_t len);
    // 测试线程-插入表格测试
    static void threadInsertTest();
    // 测试线程-删除表格测试
    static void threadDeleteTest();
    // 测试线程-更新表格测试
    static void threadUpdateTest(int row,int data);
    // 测试线程-搜索表格测试
    static void threadFindTest(int col,int l,int h);
    // 多线程并行测试(插入和搜索)
    static void multiThreadTest(int col,int l,int h);
};


#endif 