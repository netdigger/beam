/* Copyright ©2016 All right reserved*/

#include "worker_thread.h"
#include "thread_pool.h"

ThreadPool ThreadPool::instance_;

ThreadPool::ThreadPool() {
}

ThreadPool::~ThreadPool() {
	for (auto it = busys_.begin(); it != busys_.end(); ++it) {
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

WorkerThread* ThreadPool::Schedule(Task& task, void* arg) {
	WorkerThread* thread;

	mutex_.Lock();
	if (idles_.empty()) {
		thread = new WorkerThread(this);
		count_ ++;
	} else {
		thread = idles_.top();
		idles_.pop();
	}
	busys_.push_front(thread);
	mutex_.Unlock();
	
	thread->Schedule(task, arg);
	return thread;
}

void ThreadPool::OnTaskFinished(WorkerThread* thread) {
	mutex_.Lock();
	for (auto it = busys_.begin(); it != busys_.end(); ++it) {
		if ((*it) != thread) continue;
		busys_.erase(it);
		break;
	}

	idles_.push(thread);
	mutex_.Unlock();
}

void ThreadPool::OnCanceled(WorkerThread* thread) {
	mutex_.Lock();
	for (auto it = busys_.begin(); it != busys_.end(); ++it) {
		if ((*it) != thread) continue;
		busys_.erase(it);
		break;
	}

	mutex_.Unlock();
}
