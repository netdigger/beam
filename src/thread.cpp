/* Copyright ©2016 All right reserved*/

#include "thread_pool.h"
#include "worker_thread.h"
#include "beam/thread.h"

Thread::Thread(Task* task, void* args) {
	thread_ = ThreadPool::Instance().Schedule(*task, args);
}

Thread::~Thread(){
	thread_->Stop();
}

int Thread::Start() {
	return thread_->Start();
}

int Thread::Stop() {
	return thread_->Stop();
}

int Thread::Join() {
	return thread_->Join();
}

