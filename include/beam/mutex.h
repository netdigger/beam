/* Copyright ©2016 All right reserved*/

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <beam/locker.h>
#include <pthread.h>

class Mutex: public Locker {
public:
	Mutex();
	virtual ~Mutex();

	int Lock();
	int Unlock();
private:
	pthread_mutex_t mutex_;
};
#endif
