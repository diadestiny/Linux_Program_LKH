//
// Created by linkaihao on 2022/10/18.
//

#include<iostream>
#include "CLMutex.h"


CLMutex::CLMutex()
{
	int  r = pthread_mutex_init(&m_Mutex, 0);
	if(r != 0)
	{
		std::cout<<"In CLMutex::CLMutex(), pthread_mutex_init error"<<std::endl;
	}
}

CLMutex::~CLMutex()
{
	int r = pthread_mutex_destroy(&m_Mutex);
	if(r != 0)
	{
		std::cout<<"In CLMutex::~CLMutex(), pthread_mutex_destroy error"<<std::endl;
	}
}

void CLMutex::Lock()
{
	int r = pthread_mutex_lock(&m_Mutex);
	if(r != 0)
	{
		std::cout<<"In CLMutex::Lock(), pthread_mutex_lock error"<<std::endl;
	}

}

void CLMutex::Unlock()
{
	int r = pthread_mutex_unlock(&m_Mutex);
	if(r != 0)
	{
		std::cout<<"In CLMutex::Unlock(), pthread_mutex_unlock error"<<std::endl;
	}
}