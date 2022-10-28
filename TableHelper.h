//
// Created by linkaihao on 2022/10/24.
//

#ifndef TABLEHELPER_H
#define TABLEHELPER_H

#include <pthread.h>
#include <vector>
#include "Record.h"
#include "BPTree.h"
#include "CLMutex.h"

using namespace std;
#define FILE_NAME "Table_Store_File" // 文件名称
#define TABLE_RECORD_SIZE (sizeof(int64_t)*(RECORD_ATTRIBUTES_NUM))//每条记录大小

class TableHelper {
public:
    // 默认构造函数 
    TableHelper();
    // 单例模式,仅创建一次
    static TableHelper* getInstance();
    // 清空表格
    void clearTable();
    // 尾行插入数据
    void insertRecordByRow();
    // 尾行删除数据
    void deleteRecordByRow();
    // 更新第row行数据
    void updateRecord(int row,int res);
    // 生成随机数据
    void generateRecord(int64_t length);
    // 从文件加载现有表格
    void loadFromTable(int fd);
    // 打印前row行,前col列的表格数据
    void printTableData(int row,int col);
    // 搜索表格第col属性attr满足[l, h]的数据,返回行号
    void searchRecord(int col, int l, int h);
    // 在第col列上创建索引
    Node<Index>* createIndex(int col);
    // 清空索引
    void clearIndex();


private:
    // 维护属性对应索引相关的B+树
    BPTree<Index>* tree;
    // vertor动态数组维护Records,动态存储数据
    vector<Record> records;
    // 存储的文件描述符
    int m_fd;
    // 返回实例
    static TableHelper *m_tablehelper;
    // TableHelper创建的互斥量
    static CLMutex* m_mutex_instance;
    // 表格数据有关的互斥量
    static CLMutex* m_mutex_table;
    // 内部初始化static互斥量
    static CLMutex *initializeMutex();
    
};


#endif 