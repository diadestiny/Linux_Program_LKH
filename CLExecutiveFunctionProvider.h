//
// Created by linkaihao on 2022/10/18.
//

#ifndef CLEXECUTIVEFUNCTIONPROVIDER_H
#define CLEXECUTIVEFUNCTIONPROVIDER_H
class CLExecutiveFunctionProvider{
public:
    CLExecutiveFunctionProvider(){}
    virtual ~CLExecutiveFunctionProvider(){}

public:
    virtual void RunExecutiveFunction() = 0;
};
#endif 
