/* Copyright ©2016 All right reserved*/

#include <beam/thread_pool.h>
#include "thread_pool_impl.h"

ThreadPool::ThreadPool() {
	impl_ = new ThreadPoolImpl();
}

ThreadPool::~ThreadPool() {
	delete impl_;
}

int ThreadPool::Schedule(Task& task, void* arg) {
	return impl_->Schedule(task, arg);
}

int ThreadPool::Wait() {
	return impl_->Wait();
}
