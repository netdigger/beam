/* Copyright ©2016 All right reserved*/

#include "worker_thread.h"
#include <stdio.h>
#include "beam/thread.h"
#include "thread_observer.h"

WorkerThread::WorkerThread(ThreadObserver* ob)
    : canceled_(false), observer_(ob) {
    ::pthread_create(&thread_, NULL, RunFunc, this);
}

WorkerThread::~WorkerThread() { Stop(); }

int WorkerThread::Stop() {
    ::pthread_cancel(thread_);
    return ::pthread_join(thread_, NULL);
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
    pthread_cleanup_push(CleanupFunc, this);
    while (true) {
        sem_.Wait();
        join_lock_.Lock();
        task_->Execute(arg_);
        join_lock_.Unlock();
        observer_->OnTaskFinished(this);
    }

    pthread_cleanup_pop(1);
    return NULL;
}

void WorkerThread::Cleanup() {
    canceled_ = true;
    observer_->OnCanceled(this);
}

void* WorkerThread::RunFunc(void* arg) {
    WorkerThread* thread = static_cast<WorkerThread*>(arg);
    return thread->Run();
}

void WorkerThread::CleanupFunc(void* arg) {
    WorkerThread* thread = static_cast<WorkerThread*>(arg);
    thread->Cleanup();
}
