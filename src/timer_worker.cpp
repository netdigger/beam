/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "timer_worker.h"
#include <stdio.h>
#include "beam/thread.h"
using namespace beam;

TimerWorker::TimerWorker(Task& task, void* args, bool once)
    : task_(task), args_(args), run_once_(once) {
    status_ = kWaiting;
    thread_ = NULL;
}

TimerWorker::~TimerWorker() {
    if (thread_ != NULL) thread_->Stop();
}

TimerWorker::Status TimerWorker::Schedule() {
    mutex_.Lock();
    status_ = kRunning;
    thread_ = Thread::Start(*this, args_);
    mutex_.Unlock();
    return status_;
}

void TimerWorker::Run(void* args) {
    ::printf("%p start running...\n", this);
    task_.Run(args);
    ::printf("%p task finished.\n", this);
    mutex_.Lock();
    if (run_once_)
        status_ = kCancelled;
    else if (kCancelled != status_)
        status_ = kWaiting;
    mutex_.Unlock();
}

int TimerWorker::Cancel() {
    ::printf("%p canceling...", this);
    mutex_.Lock();
    status_ = kCancelled;
    if (kRunning == status_) thread_->Stop();
    thread_ = NULL;
    ::printf("finished.\n");
    mutex_.Unlock();
    return 0;
}
