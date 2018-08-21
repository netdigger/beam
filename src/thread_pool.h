/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <list>
#include <stack>
#include "beam/mutex.h"
#include "thread_observer.h"

class Task;
class WorkerThread;

class ThreadPool: public ThreadObserver {
public:
	~ThreadPool();
	static ThreadPool& Instance() {return instance_;};
	
	/* 
	 * Schedule a task;
	 * @param task The Scheduled task;
	 */
	WorkerThread* Schedule(Task&, void*);
private:
	static ThreadPool instance_;
	
	int count_; // thread count;
	Mutex mutex_;

	std::stack<WorkerThread*> idles_;
	std::list<WorkerThread*> busys_;

	ThreadPool();
	ThreadPool(ThreadPool&){};
	
	// Thread Observer
	void OnTaskFinished(WorkerThread*);
	void OnCanceled(WorkerThread*);
};
#endif

