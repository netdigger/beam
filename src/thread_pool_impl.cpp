/* Copyright ©2016 All right reserved*/

#include <beam/auto_lock.h>
#include "thread_pool_impl.h"
#include "worker_thread.h"

ThreadPoolImpl::~ThreadPoolImpl() {
	std::list<WorkerThread*>::iterator it = busys_.begin();
	for (; it != busys_.end(); ++it) {
		(*it)->Stop();
		delete *it;
	}
	busys_.clear();

	while(!idles_.empty()) {
		WorkerThread* item = idles_.top();
		delete item;
		idles_.pop();
	}
}

int ThreadPoolImpl::Schedule(Task& task, void* arg) {
	WorkerThread* thread;

	mutex_.Lock();
	if (idles_.empty()) {
		thread = new WorkerThread(this);
		count_ ++;
	}
	else {
		thread = idles_.top();
		idles_.pop();
		busys_.push_front(thread);
	}
	mutex_.Unlock();
	
	return thread->Schedule(task, arg);
}

int ThreadPoolImpl::Wait() {
	return 0;
}

void ThreadPoolImpl::MoveToIdles(WorkerThread* thread) {
	mutex_.Lock();
	std::list<WorkerThread*>::iterator it = busys_.begin();
	for (; it != busys_.end(); ++it) {
		if ((*it) != thread) continue;
		busys_.erase(it);
	}

	idles_.push(thread);
	mutex_.Unlock();
}

