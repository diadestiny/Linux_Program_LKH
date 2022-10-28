//
// Created by linkaihao on 2022/10/18.
//

#ifndef CLTHREAD_H
#define CLTHREAD_H

#include <pthread.h>
#include <iostream>
#include "CLExecutive.h"

class CLThread : public CLExecutive{
public:
    explicit CLThread(CLExecutiveFunctionProvider* pExecutiveFunctionProvider);
    virtual ~CLThread();
    virtual void Run();
    virtual void WaitForDeath();

private:
    static void* StartFunctionOfThread(void* pContext);
    pthread_t m_ThreadID;

};


#endif 
