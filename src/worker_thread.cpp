/* Copyright ©2016 All right reserved*/

#include <beam/thread.h>
#include "thread_pool.h"
#include "worker_thread.h"

WorkerThread::WorkerThread(ThreadPool* pool): pool_(pool) {
	::pthread_create(&thread_, NULL, RunFunc, this);
}

WorkerThread::~WorkerThread() {
	Stop();
}

int WorkerThread::Start() {
	return sem_.Post();
}

int WorkerThread::Stop() {
	return ::pthread_cancel(thread_);
}

int WorkerThread::Join() {
	join_lock_.Lock();
	join_lock_.Unlock();
	return 0;
}

int WorkerThread::Schedule(Task& task, void* arg) {
	task_ = &task;
	arg_ = arg;
	sem_.Post();
	return 0;
}

void* WorkerThread::Run() {
	while(true) {
		sem_.Wait();
		join_lock_.Lock();
		task_->Execute(arg_);
		join_lock_.Unlock();
		pool_->MoveToIdles(this);
	}
	return NULL;
}

void* WorkerThread::RunFunc(void* arg) {
	WorkerThread* thread = static_cast<WorkerThread*>(arg);
	return thread->Run();
}
