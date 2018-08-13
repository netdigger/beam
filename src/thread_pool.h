/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

class ThreadPoolImpl;
class Task;
class WorkerThread;

class ThreadPool {
public:
	~ThreadPool();
	static ThreadPool& Instance() {return instance_;};
	
	/* 
	 * Schedule a task;
	 * @param task The Scheduled task;
	 */
	WorkerThread* Schedule(Task&, void*);
	int Wait();
private:
	static ThreadPool instance_;

	ThreadPoolImpl* impl_;

	ThreadPool();
	ThreadPool(ThreadPool&){};
};
#endif

