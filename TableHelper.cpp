//
// Created by linkaihao on 2022/10/18.
//

#include "CLMutex.h"
#include "TableHelper.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "utils.cpp"
#include "BPTree.cpp"

//初始化互斥量
CLMutex *TableHelper::m_mutex_instance = TableHelper::initializeMutex();
CLMutex *TableHelper::m_mutex_table = TableHelper::initializeMutex();
TableHelper* TableHelper::m_tablehelper = NULL;
// 默认构造函数
TableHelper::TableHelper()
{
    // 初始化文件指针
    int fd = open(FILE_NAME, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    m_fd = fd;
    // 初始化清空表格
    records.clear();
    // 加载数据
    loadFromTable(fd); //初始化加载存储文件
    // 设置随机种子
    srand((unsigned)time(NULL));
    m_mutex_table = new CLMutex();
    
}
// 互斥量初始化
CLMutex *TableHelper::initializeMutex()
{
    CLMutex *p = new CLMutex;
    return p;
}

//单例模式 获得实例
TableHelper* TableHelper::getInstance()
{
    if(m_tablehelper){
        return m_tablehelper;
    }else{
        m_mutex_instance->Lock();//加锁,初始化实例
        m_tablehelper = new TableHelper;
        m_mutex_instance->Unlock();
    }
    return m_tablehelper;
}

// 尾行删除数据
void TableHelper::deleteRecordByRow(){
    m_mutex_table->Lock(); //加锁
    records.pop_back();
    m_mutex_table->Unlock();//解锁
}

// 清空表格
void TableHelper::clearTable(){
    records.clear(); //清空之前的表格
    clearIndex(); //清空之前的索引
    if(access(FILE_NAME, F_OK) == 0){ //删除之前的存储文件
        remove(FILE_NAME);
    }
}
// 清空索引文件
void TableHelper::clearIndex(){
    for(int col = 0 ; col < RECORD_ATTRIBUTES_NUM; col ++ ){
        string index_name = "save_index_";
        string scol = to_string(col);
        index_name = index_name + scol;
        // 逐个定位索引文件
        if (access(index_name.c_str(), F_OK) == 0) {
            remove(index_name.c_str());
        }else{
            continue;
        }
    }
}
// 生成随机数据
void TableHelper::generateRecord(int64_t length)
{
    clearTable();
    m_fd = open(FILE_NAME, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    lseek(m_fd, 0, SEEK_SET); //游标指向0重新开始写
    for (int i = 0; i < length; i++){
        m_tablehelper->insertRecordByRow();
    }
    std::cout<<"随机生成"<<length<<"行数据成功"<<std::endl;
}

//表格最后行随机插入数据
void TableHelper::insertRecordByRow()
{
    m_mutex_table->Lock(); //加锁
    lseek(m_fd, 0, SEEK_END);
    Record rec;
    rec.setId(records.size());
    rec.setAttributesByRandom(); //在行末随机插入一行数据
    records.push_back(rec);
    write(m_fd, (char*)&rec.m_attributes, TABLE_RECORD_SIZE);  // 写入存储文件
    m_mutex_table->Unlock();//解锁

}

// 更新第row行数据
void TableHelper::updateRecord(int row,int res){
    m_mutex_table->Lock(); //加锁
    records[row].setAttributesByNum(res);
    m_mutex_table->Unlock();//解锁
}

//从文件中加载已经存在的表
void TableHelper::loadFromTable(int fd)
{
    lseek(fd, 0, SEEK_SET); //文件指针位于起始位置
    Record rec;
    while(read(fd,(char*)&rec.m_attributes, sizeof(rec.m_attributes))){
        records.push_back(rec);
    }
}


Node<Index>* TableHelper::createIndex(int col){
    tree->BPTree_Create(); //初始化创建B+树
    auto root = tree->BPTree_Getroot();
    Record res; //定义虚拟根节点
    res.setId(-1);
    res.setAttributesByNum(0x3f3f3f3f); 
    Index index_node;
    index_node.val = res.getAttributesByCol(col);
    index_node.major_id = res.getId();
    this->tree->BPTree_Insert_Node(root,index_node);
    // 建议索引B+树
    std::cout<<"开始在属性"<<col<<"列上建立索引"<<std::endl;
    for(int i = 0 ; i < records.size() ; i++){
        index_node.val = records[i].getAttributesByCol(col);
        index_node.major_id = records[i].getId();
        this->tree->BPTree_Insert_Node(root, index_node); 
    }
    return root;
}

//区域搜索
void TableHelper::searchRecord(int col, int l, int h) {
    this->tree = new BPTree<Index>; //初始化索引B+树
    Node<Index>* root = ReadIndexFile<Index>(col); //从索引文件读取索引B+树
    if(root){ //索引存在则加速搜索
        std::cout<<"属性"<<col<<"列索引读取成功"<<std::endl;
        std::cout<<"第"<<col<<"列属性满足在["<<l<<","<<h<<"]范围,有以下数据:"<<std::endl;
        tree->BPTree_Find_Range(root, l,h);
    }else{
        //在col列属性建立索引,再搜索
        auto root = createIndex(col);
        std::cout<<"第"<<col<<"列属性满足在["<<l<<","<<h<<"]范围,有以下数据:"<<std::endl;
        tree->BPTree_Find_Range(root, l,h);
        SaveIndexFile<Index>(root, col); //保存为索引文件
    }
}


//打印表格
void TableHelper::printTableData(int row,int col)
{
    std::cout<<"表格总行数:"<<this->records.size()<<" ,仅显示前"<<row<<"行, 前"<<col<<"列"<<std::endl;
    printf("       ");
    for(int j=0;j < col;j++){
        printf("attr%d",j+1);
        if(j<col-1) std::cout<<" | ";
    }
    std::cout<<std::endl;
    for(int k=0;k<85;k++) std::cout<<"-";
    std::cout<<std::endl;

    for(int i = 0 ; i < row; i++){
        printf("row %d:",i);
        for(int j=0;j < col;j++){
            printf("%5ld",records[i].getAttributesByCol(j));
            if(j<col-1) std::cout<<" | ";
        }
        std::cout<<std::endl;
        for(int k=0;k<85;k++) std::cout<<"-";
        std::cout<<std::endl;
    }
}
