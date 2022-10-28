//
// Created by linkaihao on 2022/10/26.
//

#include "ThreadTest.h"
#include "TableHelper.h"
#include "CLExecutiveFunctionProvider.h"
#include "MyCLExecutiveFunction.h"
#include "CLThread.h"
#include "CLExecutive.h"

// 测试线程-随机生成表格(len行)
void ThreadTest::threadGenerateTest(int64_t len){
    std::cout<<"启动生成数据测试线程:"<<std::endl;
    CLExecutiveFunctionProvider* generate = new CLExecutive_Build(len);
    CLExecutive *thread_generate = new CLThread(generate);
    thread_generate->Run();
    thread_generate->WaitForDeath();
}
    
// 测试线程-插入表格测试
void ThreadTest::threadInsertTest(){
    std::cout<<"启动插入数据测试线程:"<<std::endl;
    CLExecutiveFunctionProvider* insert = new CLExecutive_Append();
    CLExecutive *thread_insert = new CLThread(insert);
    thread_insert->Run();
    thread_insert->WaitForDeath();
}

// 测试线程-删除表格测试
void ThreadTest::threadDeleteTest(){
    std::cout<<"启动删除数据测试线程:"<<std::endl;
    CLExecutiveFunctionProvider* insert = new CLExecutive_Delete();
    CLExecutive *thread_delete = new CLThread(insert);
    thread_delete->Run();
    thread_delete->WaitForDeath();
}
// 测试线程-更新表格测试
void ThreadTest::threadUpdateTest(int row,int data){
    std::cout<<"启动更新数据测试线程:"<<std::endl;
    CLExecutiveFunctionProvider* insert = new CLExecutive_Update(row,data);
    CLExecutive *thread_update = new CLThread(insert);
    thread_update->Run();
    thread_update->WaitForDeath();
}

// 测试线程-搜索表格测试
void ThreadTest::threadFindTest(int col,int l,int h){
    CLExecutiveFunctionProvider* search = new CLExecutive_Find(col, l, h);
    CLExecutive * thread_find = new CLThread(search);
    thread_find->Run();
    thread_find->WaitForDeath();
}

// 多线程并行测试(插入和搜索)
void ThreadTest::multiThreadTest(int col,int l,int h){
    CLExecutiveFunctionProvider* insert1 = new CLExecutive_Append();
    CLExecutiveFunctionProvider* search1 = new CLExecutive_Find(col, l, h);
    CLExecutiveFunctionProvider* insert2 = new CLExecutive_Append();
    CLExecutiveFunctionProvider* search2 = new CLExecutive_Find(col, l, h);
    CLExecutive *thread_update1 = new CLThread(insert1);
    CLExecutive *thread_find1 = new CLThread(search1);
    CLExecutive *thread_update2 = new CLThread(insert2);
    CLExecutive *thread_find3 = new CLThread(search2);
    thread_update1->Run();
    thread_update2->Run();
    thread_find1->Run();
    thread_find3->Run();
    thread_update1->WaitForDeath();
    thread_find1->WaitForDeath();
    thread_update2->WaitForDeath();
    thread_find3->WaitForDeath();
}






// void create_b_plus_tree(int length, int col, int left, int right)
// {
//     CLExecutiveFunctionProvider* Generate = new CLExecutive_Build(length);
//     CLExecutive * thread1 = new CLThread(Generate);
//     thread1->Run();
//     thread1->WaitForDeath();
//     CLExecutiveFunctionProvider* Search = new CLExecutive_Find(col, left, right);
//     CLExecutive * thread = new CLThread(Search);
//     thread->Run();
//     thread->WaitForDeath();
// }