/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_POOL_IMPL_H__
#define __THREAD_POOL_IMPL_H__
#include <beam/mutex.h>
#include <stack>
#include <list>

class WorkerThread;
class Task;

class ThreadPoolImpl {
public:	
	~ThreadPoolImpl();

	/* 
	 * Schedule a task;
	 * @param task The Scheduled task;
	 */
	int Schedule(Task&, void*);
	int Wait();

	void MoveToIdles(WorkerThread*);

	int count_; // thread count;

	Mutex mutex_;

	std::stack<WorkerThread*> idles_;
	std::list<WorkerThread*> busys_;
};
#endif

