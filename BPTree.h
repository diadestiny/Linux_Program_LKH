//
// Created by linkaihao on 2022/10/18.
//

#ifndef BPTREE_H
#define BPTREE_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>
#include "Record.h"

#define TREE_RANK 4 //定义B+树的阶数

// 定义索引节点数据
typedef struct Index
{
    int64_t val; //属性值
    int64_t major_id; //主键
}Index;


// B+树节点
template <typename T>
class Node{
public:
    Node();
    virtual ~Node();
    bool is_leaf;
    Node<T>* next;
    Node<T>** childs; //指针形式定义孩子子树,初始化分配为TREE_RANK个
    int num; //当前使用量
    T* index_node; //指针形式定义索引node,初始化分配为TREE_RANK+1个
};

template <typename T>
class BPTree{
public:
    // 自定义默认构造函数,定义阶数
    BPTree():rank(TREE_RANK){};
    // 创建B+树
    void BPTree_Create();
    // 创建结点
    Node<T>* BPTree_Create_Node();
    // 销毁结点 
    void BPTree_Destroy_Node(Node<T>** node);
    // 返回B+树根结点
    Node<T>* BPTree_Getroot();
    // 从第c层开始打印B+树 
    void BPTree_Print(Node<T> *node, int c);
    // 插入B+树结点(所有情况)
    void BPTree_Insert_Node(Node<T>* root, const T& index_node);
    //插入B+树的未满结点(未满结点情况)
    void BPTree_Insert_Node_NotFull(Node<T>* node, const T& index_node);
    //从root索引结点开始,搜索属性在[low,right]的行
    void BPTree_Find_Range(Node<T>* root, int low, int high);

    

private:
    Node<T>* root; //根节点
    int rank; //b+树的阶数

};

#endif 
