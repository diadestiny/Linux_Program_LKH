//
// Created by linkaihao on 2022/10/18.
//

#ifndef CLMutex_H
#define CLMutex_H

#include <pthread.h>

class CLMutex{
public:

	CLMutex();
	virtual ~CLMutex();

	void Lock();
	void Unlock();

private:
	CLMutex(const CLMutex&);
	CLMutex& operator=(const CLMutex&);

private:
	pthread_mutex_t m_Mutex;
};

#endif