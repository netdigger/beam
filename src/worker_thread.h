/* Copyright ©2016 All right reserved*/

#ifndef __WORKER_THREAD_H__
#define __WORKER_THREAD_H__
#include <beam/task.h>
#include <beam/semaphore.h>

class Thread;
class ThreadPoolImpl;
class WorkerThread: public Task {
public:
	WorkerThread(ThreadPoolImpl*);
	~WorkerThread();
	
	int Schedule(Task&, void*);
private:
	Thread* thread_;
	Task* task_;
	void* arg_;

	Semaphore sem_;

	void Execute(void*);
};
#endif

