/* Copyright ©2016 All right reserved*/

#include "worker_thread.h"
#include "beam/task.h"
#include "beam/thread.h"
#include "thread_observer.h"

using namespace beam;
WorkerThread::WorkerThread(ThreadObserver* ob)
    : idle_(true), canceled_(false), deleted_(false), observer_(ob) {
    task_ = NULL;
    ::pthread_create(&thread_, NULL, RunFunc, this);
}

WorkerThread::~WorkerThread() {
    deleted_ = true;
    ::pthread_cancel(thread_);
    ::pthread_join(thread_, NULL);
}

int WorkerThread::Stop() {
    if (idle_ || canceled_) return 0;
    ::pthread_cancel(thread_);
    return ::pthread_join(thread_, NULL);
}

int WorkerThread::Join() {
    if (idle_ || canceled_) return 0;
    join_lock_.Lock();
    return join_lock_.Unlock();
}

int WorkerThread::Schedule(Task& task, void* arg) {
    join_lock_.Lock();
    idle_ = false;
    task_ = &task;
    arg_ = arg;
    return sem_.Post();
}

void* WorkerThread::Run() {
    pthread_cleanup_push(CleanupFunc, this);
    while (true) {
        sem_.Wait();
        if (NULL != task_) task_->Run(arg_);
        task_ = NULL;
        observer_->OnFinished(this);
        idle_ = true;
        join_lock_.Unlock();
    }

    pthread_cleanup_pop(1);
    return NULL;
}

void WorkerThread::Cleanup() {
    if (deleted_) return;
    canceled_ = idle_ = true;
    observer_->OnFinished(this);
    join_lock_.TryLock();
    join_lock_.Unlock();
}

void* WorkerThread::RunFunc(void* arg) {
    WorkerThread* thread = static_cast<WorkerThread*>(arg);
    return thread->Run();
}

void WorkerThread::CleanupFunc(void* arg) {
    WorkerThread* thread = static_cast<WorkerThread*>(arg);
    thread->Cleanup();
}
