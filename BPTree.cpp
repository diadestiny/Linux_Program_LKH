//
// Created by linkaihao on 2022/10/18.
//

#include "BPTree.h"

// 创建B+树结点
template <typename T>
Node<T>* BPTree<T>::BPTree_Create_Node()
{
    Node<T>* node = (Node<T>*)malloc(sizeof(Node<T>));
    node->index_node = (T*)malloc((TREE_RANK+1)*sizeof(T)); //分配(TREE_RANK+1)个索引结点空间,+1是为了方便处理分裂时的根节点
    node->childs = (Node<T>**)malloc((TREE_RANK)*sizeof(Node<T>)); //分配子树指针数组
    node->is_leaf = true;
    node->num = 0;
    node->next = NULL;
    return node;
}

// 创建B+树
template <typename T>
void BPTree<T>::BPTree_Create()
{
    Node<T>* node = BPTree_Create_Node();
    this->root = node;
}

// 返回根结点
template <typename T>
Node<T>* BPTree<T>::BPTree_Getroot(){
    return this->root;
}

//释放结点顺序，先释放内部数据，再释放node
template <typename T>
void BPTree<T>::BPTree_Destroy_Node(Node<T>* node){
    free(node->childs);
    free(node->index_node);
    free(node);
}


template <typename T>
void BPTree<T>::BPTree_Insert_Node_Free(Node<T>* node, const T &index_node){
    int p; //移动下标p
    // 按大小顺序,向右移动结点,找到适合插入的p位置
    for(p = node->num;p >= 1 && index_node.val < node->index_node[p - 1].val;p--){
        node->index_node[p] = node->index_node[p - 1];
    }
    node->num = node->num + 1; //数量+1
    node->index_node[p] = index_node; //插入
}

// 分裂结点,以(TREE_RANK+1)/2号结点为分界点,左右分裂
template <typename T>
void BPTree<T>::BPTree_Insert_Node_Split(Node<T>* root, const T &index_node){
    BPTree_Insert_Node_Free(root, index_node); //先插入
    Node<T>* left_node = BPTree_Create_Node(); //分裂左结点
    Node<T>* right_node = BPTree_Create_Node();  //分裂右结点
    left_node->num = (TREE_RANK+1)/2;
    right_node->num = (TREE_RANK+1)/2;
    right_node->next = root->next; 
    left_node->next = right_node; //左右连接
    for(int i = 0 ; i < (TREE_RANK+1)/2; i++ ){
        left_node->index_node[i] = root->index_node[i];
        right_node->index_node[i] = root->index_node[i + (TREE_RANK+1)/2];
    }
    //将分界结点作为root结点,赋值相关数据
    root->index_node[0] = left_node->index_node[(TREE_RANK+1)/2 - 1];
    root->index_node[1] = right_node->index_node[(TREE_RANK+1)/2 - 1];
    root->childs[0] = left_node;
    root->childs[1] = right_node;
    root->is_leaf = false;
    root->num = 2;
}

// 插入结点整体逻辑
template <typename T>
void BPTree<T>::BPTree_Insert_Node(Node<T>* root, const T &index_node)
{
    // 如果不是叶子结点,递归往下搜索
    if(!root->is_leaf){
        for(int pos = 0 ; pos< root->num ; pos++){
            if(root->index_node[pos].val > index_node.val){
                BPTree_Insert_Node(root->childs[pos], index_node);
                return;
            }
        }
        // 按大小顺序找到合适的pos下标
    }
    else{ //为叶子结点进行处理
        if(root->num>=TREE_RANK){
            //节点满了,则以(TREE_RANK+1)/2号结点为分界点,左右分裂
            BPTree_Insert_Node_Split(root,index_node);
        }else{// 节点未满,可以直接插入
             BPTree_Insert_Node_Free(root, index_node);
        }
    }
}


//从root索引结点开始,搜索属性在[left,right]的行
template <typename T>
void BPTree<T>::BPTree_Find_Range(Node<T>* root, int low, int high) {
    // 非叶子结点,继续往下搜索
    if(!root->is_leaf){
        for(int i = 0 ; i< root->num ; i++){
            if(root->index_node[i].val >= low){
                BPTree_Find_Range(root->childs[i], low, high);
            }
            return;
        }
    }else{ //到达叶子结点则按序搜索
        while(root){
            for(int i=0;i<root->num && root->index_node[i].val>=low && root->index_node[i].val<=high;i++){
                std::cout<<"第"<<root->index_node[i].major_id<<"行, "<<"属性值:"<<root->index_node[i].val<<std::endl;
            }
            root = root->next;
        }
        
    }    
}
// 打印B+树
template <typename T>
void BPTree<T>::BPTree_Print(Node<T> *node, int c) {
    Node<T> *p = node;
    int i;
    if (p != NULL) {
        printf("\n第%d层 结点数量:%d 是否叶子结点层:%d\n", c, p->num, p->is_leaf); //打印keys
        for (i = 0; i < node->num; i++)
            printf("属性值:%ld 主键行号:%ld  ", p->index_node[i].val,p->index_node[i].major_id);
        printf("\n");
        c++;
        for (i = 0; i <= p->num; i++)
            if (p->childs[i])
                BPTree_Print(p->childs[i], c);  //递归打印所有子树
    }
    else printf("空树\n");
}