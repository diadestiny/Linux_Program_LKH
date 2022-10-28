//
// Created by linkaihao on 2022/10/18.
//

#include "Record.h"
#include <iostream>
//设置主键
void Record::setId(int64_t id){
    m_id = id;
}
// 获取主键
int64_t Record::getId(){
    return m_id;
}
// 随机生成属性值
void Record::setAttributesByRandom(){
    for(int i=0;i<RECORD_ATTRIBUTES_NUM;i++){
        m_attributes[i] = (rand() % 2000) + 1;
    }
}
// 用一组arrays生成属性值
void Record::setAttributesByArray(int64_t* arrays){
    for(int i=0;i<RECORD_ATTRIBUTES_NUM;i++){
        m_attributes[i] = arrays[i];
    }
}
// 用固定的特定数值生成属性值
void Record::setAttributesByNum(int64_t num){
    for(int i=0;i<RECORD_ATTRIBUTES_NUM;i++){
        m_attributes[i] = num;
    }
}
// 返回第col列属性值
int64_t Record::getAttributesByCol(int64_t col){
    return m_attributes[col];
}

