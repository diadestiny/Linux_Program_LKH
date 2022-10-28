//
// Created by linkaihao on 2022/10/18.
//

#ifndef RECORD_H
#define RECORD_H

#define RECORD_ATTRIBUTES_NUM 100 //每行的属性数量
#include <cstdint>


// 表格每行存储的记录项Record
class Record{
public:
    //设置主键
    void setId(int64_t id);
    // 获取主键
    int64_t getId();
    // 随机生成属性值
    void setAttributesByRandom();
    // 随机生成属性值
    void setAttributesByWrite();
    // 用一组arrays生成属性值
    void setAttributesByArray(int64_t* arrays);
    // 用固定的特定数值生成属性值
    void setAttributesByNum(int64_t num);
    // 返回第col列属性值
    int64_t getAttributesByCol(int64_t col);
private:
    int64_t m_id; //行号,主键
    int64_t m_attributes[RECORD_ATTRIBUTES_NUM]; //LEN_ATTRIBUTES个属性,本程序设置为100 
    friend class TableHelper; //定义友元类
};


#endif 
