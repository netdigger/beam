/* Copyright ©2016 All right reserved*/

#include <beam/thread.h>
#include "thread_pool_impl.h"
#include "worker_thread.h"

WorkerThread::WorkerThread(ThreadPoolImpl* pool) {
	thread_ = new Thread(this, pool);
	thread_->Start();
}

WorkerThread::~WorkerThread() {
	thread_->Stop();
	delete thread_;
}

int WorkerThread::Schedule(Task& task, void* arg) {
	task_ = &task;
	arg_ = arg;
	sem_.Post();
	return 0;
}

void WorkerThread::Execute(void* arg) {
	ThreadPoolImpl* pool = static_cast<ThreadPoolImpl*>(arg);

	while(true) {
		sem_.Wait();
		task_->Execute(arg_);
		pool->MoveToIdles(this);
	}
}
