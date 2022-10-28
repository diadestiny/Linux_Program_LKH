//
// Created by linkaihao on 2022/10/18.
//

#include "CLThread.h"

CLThread::CLThread(CLExecutiveFunctionProvider *pExecutiveFunctionProvider): CLExecutive(pExecutiveFunctionProvider) {}

CLThread::~CLThread() noexcept {}

void *CLThread::StartFunctionOfThread(void* pContext) {
    CLThread* pThreadThis = (CLThread*)pContext;
    pThreadThis->m_pExecutiveFunctionProvider->RunExecutiveFunction();
    std::cout<<"启动CLThread(指针地址:"<<pThreadThis <<")"<<std::endl;
    return 0;
}

void CLThread::Run() {
    int r = pthread_create(&m_ThreadID, 0, StartFunctionOfThread, this);
    if(r!=0){
        std::cout<<"In CLThread::Run(), thread create error!"<<std::endl;
        return ;
    }
}

void CLThread::WaitForDeath() {
    int r = pthread_join(m_ThreadID, 0);
    if(r!=0)
    {
        std::cout<<"In CLThread::WaitForDeath(), thread delete error!"<<std::endl;
        return ;
    }
}
