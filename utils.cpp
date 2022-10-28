//
// Created by linkaihao on 2022/10/18.
//


#include "BPTree.h"
#include <iostream>
#include <string>

using namespace std;
// 将基于B+树建立的索引保存为文件形式
template <typename T>
void SaveIndexFile(Node<T>* root, int col) {
    string index_name = "save_index_";
    string scol = to_string(col);
    index_name = index_name + scol;
    //先删除原有索引文件
    int aid = access(index_name.c_str(), F_OK);
    if (aid == 0){ //文件存在
        int rid = remove(index_name.c_str()); //删除
        if (rid==-1) std::cout<<"删除索引失败"<<std::endl;
    }else{
        // 保存索引文件
        int fd = open(index_name.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd != -1){
            WriteBPTreeNode(fd, root);
            std::cout<<"索引文件创建成功"<<std::endl;
            close(fd);
        }else{
            std::cout<<"索引文件创建失败"<<std::endl;
        }
    }
    
}

//将B+树索引节点写入文件
template <typename T>
void WriteBPTreeNode(int &fd, Node<T>* node) {
    if(node){
        int wid = write(fd, node, sizeof(Node<T>));
        if(wid!=-1){
            for (int i = 0; i < node->num; i++){
                WriteBPTreeNode(fd, node->childs[i]); //递归写入
            }
        }else{
            std::cout<<"索引写入文件失败"<<std::endl;
        }        
    }else{
        return;
    }
   
}

//从文件读取基于B+树建立的索引
template <typename T>
Node<T>* ReadIndexFile(int col) {
    string index_name = "save_index_";
    string scol = to_string(col);
    index_name = index_name + scol;
    // std::cout<<index_name.c_str();
    int aid = access(index_name.c_str(), F_OK);
    if (aid == 0){
        int fd = open(index_name.c_str(), O_RDONLY, S_IRUSR | S_IWUSR);
        if(fd != -1){
            Node<T>* last_node = NULL; //读取的前叶节点
            Node<T>* node = ReadBPTreeNode(fd, last_node);
            close(fd);
            // std::cout<<"索引文件读取成功"<<std::endl;
            return node;
        }else{
            std::cout<<access(index_name.c_str(), F_OK);
            std::cout<<fd;
            return NULL;
        }
    }else{
        std::cout<<"索引文件不存在"<<std::endl;
    }
    return NULL;
}

//读取B+树索引节点
template <typename T>
Node<T>* ReadBPTreeNode(int fd, Node<T>* &last_node) {
    Node<T>* node = (Node<T>*)malloc(sizeof(Node<T>));
    node->index_node = (T*)malloc((TREE_RANK+1)*sizeof(T)); //分配(TREE_RANK+1)个索引结点空间,+1是为了方便处理分裂时的根节点
    node->childs = (Node<T>**)malloc((TREE_RANK)*sizeof(Node<T>)); //分配子树指针数组
    node->is_leaf = true;
    node->num = 0;
    node->next = NULL;
    if(node){
        int rid = read(fd, node, sizeof(Node<T>));
        if(rid != -1){
            if (node->is_leaf) { //叶子结点处理逻辑
                if (last_node){
                    last_node->next = node;
                }
                last_node=node; //赋值前结点,返回递归读取
                return node;
            }
            for (int i = 0; i < node->num; i++)
                node->childs[i] = ReadBPTreeNode(fd,last_node); //递归读取
        }
    }
    return node;
}
