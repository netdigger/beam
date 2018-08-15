/* Copyright ©2016 All right reserved*/

#ifndef __WORKER_THREAD_H__
#define __WORKER_THREAD_H__
#include <pthread.h>
#include "beam/mutex.h"
#include "beam/semaphore.h"

class ThreadPool;
class Task;
class WorkerThread {
public:
	WorkerThread(ThreadPool*);
	~WorkerThread();
	
	int Schedule(Task&, void*);
	int Stop();
	int Join();
	int Start();
private:
	pthread_t thread_;

	void* arg_;
	Task* task_;
	ThreadPool* pool_;

	Semaphore sem_;
	Mutex join_lock_;

	void Execute(void*);
	void* Run();
	void Cleanup();
	static void* RunFunc(void*);
	static void CleanupFunc(void*);
};
#endif

