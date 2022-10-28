//
// Created by linkaihao on 2022/10/18.
//

#include "CLExecutiveFunctionProvider.h"
#include "TableHelper.h"
#ifndef MYCLEXECUTIVEFUNCTION_H
#define MYCLEXECUTIVEFUNCTION_H

class CLExecutive_Build: public CLExecutiveFunctionProvider {
public:
    CLExecutive_Build(int size):m_size(size){}

    virtual ~CLExecutive_Build() {}

    virtual void RunExecutiveFunction() {
        TableHelper* tabelhelper = TableHelper::getInstance();
        tabelhelper->generateRecord(m_size);
    }

private:
    int m_size; //长度
};


class CLExecutive_Append: public CLExecutiveFunctionProvider {
public:
    CLExecutive_Append() {}

    virtual ~CLExecutive_Append() {}

    virtual void RunExecutiveFunction() {
        TableHelper* tabelhelper = TableHelper::getInstance();
        tabelhelper->insertRecordByRow();
    }
};

class CLExecutive_Delete: public CLExecutiveFunctionProvider {
public:
    CLExecutive_Delete() {}
    virtual ~CLExecutive_Delete() {}
    virtual void RunExecutiveFunction() {
        TableHelper* tabelhelper = TableHelper::getInstance();
        tabelhelper->deleteRecordByRow();
    }
};

class CLExecutive_Update: public CLExecutiveFunctionProvider {
public:
    CLExecutive_Update(int row,int data):m_row(row),m_data(data){}
    virtual ~CLExecutive_Update() {}

    virtual void RunExecutiveFunction() {
        TableHelper* tabelhelper = TableHelper::getInstance();
        tabelhelper->updateRecord(m_row,m_data);
    }
private:
    int m_row; //待更新行
    int m_data; //更新结果
};

class CLExecutive_Find:public CLExecutiveFunctionProvider{
public:

    CLExecutive_Find(int col, int l,int h):m_l(l),m_h(h),m_col(col){}
    virtual ~CLExecutive_Find(){}
    virtual void RunExecutiveFunction(){
        TableHelper* tabelhelper = TableHelper::getInstance();
        tabelhelper->searchRecord(m_col, m_l, m_h);
    }

private:
    int m_l; 
    int m_h;
    int m_col;
};

#endif 
