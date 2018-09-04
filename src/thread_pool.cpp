/* Copyright ©2016 All right reserved*/

#include "thread_pool.h"
#include "beam/auto_lock.h"
#include "worker_thread.h"

using namespace beam;
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
    WorkerThread* thread = NULL;

    mutex_.Lock();
    while (!idles_.empty() && thread == NULL) {
        thread = idles_.top();
        idles_.pop();
        // If thread was canceled, it should be cleared
        if (thread->IsCanceled()) {
            delete thread;
            thread = NULL;
        }
    }

    if (NULL == thread) {
        thread = new WorkerThread(this);
    }
    busys_.push_front(thread);
    mutex_.Unlock();

    thread->Schedule(task, arg);
    return thread;
}

void ThreadPool::OnFinished(WorkerThread* thread) {
    mutex_.Lock();
    for (auto it = busys_.begin(); it != busys_.end(); ++it) {
        if ((*it) != thread) continue;
        busys_.erase(it);
        break;
    }

    idles_.push(thread);
    mutex_.Unlock();
}
