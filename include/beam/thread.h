/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_H__
#define __THREAD_H__

#include <beam/task.h>
#include <pthread.h>

class Thread {
public:
	Thread(Task* task, void*);
	~Thread();

	int Start();
	int Stop();
	int Join();
private:
	Task* task_;
	void* args_;
	pthread_t thread_;

	static void* Func(void*); 
};
#endif

