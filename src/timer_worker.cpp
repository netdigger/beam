/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "timer_worker.h"
#include "beam/auto_lock.h"
#include "beam/thread.h"
using namespace beam;

TimerWorker::TimerWorker(Task& task, void* args, bool once)
    : task_(task), args_(args), run_once_(once) {
    status_ = kWaiting;
}

Timer::Status TimerWorker::Schedule() {
    AutoLock lock(mutex_);
    if (kStopped == status_) return kStopped;
    status_ = kRunning;
    thread_ = Thread::Start(task_, args_);
    return status_;
}

void TimerWorker::Run(void* args) {
    task_.Run(args);
    mutex_.Lock();
    if (run_once_)
        status_ = kStopped;
    else if (kStopped != status_)
        status_ = kWaiting;
    mutex_.Unlock();
}

Timer::Status TimerWorker::Stop() {
    AutoLock lock(mutex_);
    if (kRunning == status_) thread_->Stop();
    status_ = kStopped;
    return status_;
}
