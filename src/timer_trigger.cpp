/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "timer_trigger.h"
#include <stdio.h>
#include "beam/task.h"
#include "beam/thread.h"

using namespace beam;
TimerTrigger::TimerTrigger(Task& task, void* args) : task_(task), args_(args) {
    // Blocking signal must be done in main thread
    sigset_t sigset;
    ::sigemptyset(&sigset);
    ::sigaddset(&sigset, SIGRTMIN);
    ::sigprocmask(SIG_BLOCK, &sigset, &old_sigset_);

    thread_ = Thread::Start(*this, NULL);
    if (init() != 0) {
        ::printf("Error in initial timer triger\n");
        thread_->Stop();
        thread_ = NULL;
    }
}

TimerTrigger::~TimerTrigger() {
    ::timer_delete(timer_id_);
    thread_->Stop();
    ::sigprocmask(SIG_SETMASK, &old_sigset_, NULL);
}

void TimerTrigger::Run(void*) {
    sigset_t sigset;
    int signum;

    ::sigemptyset(&sigset);
    ::sigaddset(&sigset, SIGRTMIN);
    while (true) {
        if (::sigwait(&sigset, &signum) != 0) {
            ::perror("sigwait faile");
            continue;
        }
        task_.Run(args_);
    }
}

int TimerTrigger::init() {
    sigevent_.sigev_notify = SIGEV_SIGNAL;
    sigevent_.sigev_signo = SIGRTMIN;
    sigevent_.sigev_value.sival_ptr = &timer_id_;
    if (::timer_create(CLOCK_REALTIME, &sigevent_, &timer_id_) == -1) {
        ::perror("timer create");
        return -1;
    }

    itime_.it_value.tv_sec = 0;
    itime_.it_value.tv_nsec = 1000000;
    itime_.it_interval.tv_sec = itime_.it_value.tv_sec;
    itime_.it_interval.tv_nsec = itime_.it_value.tv_nsec;

    if (::timer_settime(timer_id_, 0, &itime_, NULL) == -1) {
        ::perror("timer settime");
        return -1;
    }
    return 0;
}
