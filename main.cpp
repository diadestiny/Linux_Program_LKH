#include <iostream>
#include "TableHelper.h"
#include "ThreadTest.h"
#include "CLThread.h"
#include "BPTree.h"



int main() {
    ThreadTest* threadtest = new ThreadTest();
    TableHelper* table_helper = TableHelper::getInstance();
    // 随机生成数据
    threadtest->threadGenerateTest(10);
    table_helper->printTableData(10,10);

    // 插入
    threadtest->threadInsertTest();
    table_helper->printTableData(11,10);
    
    // 更新
    threadtest->threadUpdateTest(10,888);
    table_helper->printTableData(11,10);

    // 删除
    threadtest->threadDeleteTest();
    table_helper->printTableData(10,10);

    // 查找
    threadtest->threadFindTest(0,100,500);
    table_helper->printTableData(10,10);

    // 基于B+树索引文件再次查找
    threadtest->threadFindTest(0,100,500);
    table_helper->printTableData(10,10);


    // 多线程测试
    threadtest->multiThreadTest(1,100,500);
    table_helper->printTableData(12,10);

    return 0;
}
