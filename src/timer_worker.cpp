/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "timer_worker.h"
#include "beam/auto_lock.h"
#include "beam/thread.h"
using namespace beam;

TimerWorker::TimerWorker(Task& task, void* args, bool once)
    : task_(task), args_(args), run_once_(once) {
    status_ = kWaiting;
}

TimerWorker::Status TimerWorker::Schedule() {
    AutoLock lock(mutex_);
    if (kCancelled == status_) return kCancelled;
    status_ = kRunning;
    thread_ = Thread::Start(task_, args_);
    return status_;
}

void TimerWorker::Run(void* args) {
    task_.Run(args);
    mutex_.Lock();
    if (run_once_)
        status_ = kCancelled;
    else if (kCancelled != status_)
        status_ = kWaiting;
    mutex_.Unlock();
}

int TimerWorker::Cancel() {
    AutoLock lock(mutex_);
    status_ = kCancelled;
    if (kRunning == status_) return thread_->Stop();
    return 0;
}
