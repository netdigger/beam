/* Copyright ©2016 All right reserved*/

#include "thread_pool.h"
#include "beam/auto_lock.h"
#include "worker_thread.h"

ThreadPool ThreadPool::instance_;

ThreadPool::~ThreadPool() {
    for (auto it = busys_.begin(); it != busys_.end(); ++it) {
        (*it)->Stop();
        delete *it;
    }
    busys_.clear();

    while (!idles_.empty()) {
        WorkerThread* item = idles_.top();
        delete item;
        idles_.pop();
    }
}

Thread* ThreadPool::DoSchedule(Task& task, void* arg) {
    WorkerThread* thread;

    mutex_.Lock();
    if (idles_.empty()) {
        thread = new WorkerThread(this);
        count_++;
    } else {
        thread = idles_.top();
        // If thread was canceled, it should be cleared
        while (thread->IsCanceled()) {
            delete thread;
            idles_.pop();
            thread = idles_.top();
        }
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
    AutoLock lock(mutex_);
    mutex_.Lock();
    for (auto it = busys_.begin(); it != busys_.end(); ++it) {
        if ((*it) != thread) continue;
        delete *it;
        busys_.erase(it);
        break;
    }

    mutex_.Unlock();
}
