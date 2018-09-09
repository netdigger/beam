/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "timer_service.h"
#include <stdio.h>
#include <unistd.h>
#include "beam/auto_lock.h"
#include "beam/timer.h"
#include "timer_trigger.h"
#include "timer_worker.h"

using namespace beam;
TimerService TimerService::instance_;

Timer* TimerService::DoAdd(Task& task, void* args, int time, bool once) {
    ::printf(" Add task....");
    AutoLock lock(mutex_);
    if (workers_.size() == 0) {
        TimerTrigger::Start(*this, NULL);
        elapsed_time_ = 0;
    }

    if (time < 0) time = 0;
    TimerWorker* timer = new TimerWorker(task, args, once);
    TimerInfo info = {timer, time, time + elapsed_time_};
    workers_.insert(info);
    ::printf(" %p added.\n", timer);
    return timer;
}

void TimerService::DoCancel(Timer* timer) {
    ::printf("Do cancel: %p\n", timer);
    AutoLock lock(mutex_);
    for (auto it = workers_.begin(); it != workers_.end(); ++it) {
        ::printf("search: woker timer %p\n", it->worker);
        if (it->worker == timer) {
            ::printf("cancel: woker timer %p... ", it->worker);
            it->worker->Cancel();
            ::printf("finished\n");
            delete it->worker;
            workers_.erase(it);
            break;
        }
    }
    ::printf("Do cancel: %p finished, %lu \n", timer, workers_.size());
}

void TimerService::Run(void*) {
    ::printf("start run: ");
    AutoLock lock(mutex_);
    elapsed_time_++;
    ::printf("elapsed time is %d start \n", elapsed_time_);
    TimerInfo info;
    auto it = workers_.begin();
    while (it != workers_.end() && elapsed_time_ >= it->trigger_time) {
        ::printf("trigger timer is %d, timer is %p:", it->trigger_time,
                 it->worker);
        if (it->worker->GetStatus() == TimerWorker::kRunning) {
            ::printf(" is running\n");
            ++it;
            continue;
        }
        info = *it;
        it = workers_.erase(it);
        if (info.worker->GetStatus() == TimerWorker::kCancelled) {
            delete info.worker;
            ::printf(" deleted.\n");
        } else {
            info.worker->Schedule();
            info.trigger_time = info.circle_time + elapsed_time_;
            workers_.insert(info);
            ::printf(" Scheduled. \n");
        }
    }

    // Be careful in trigger's task stop trigger.
    if (workers_.empty()) {
        ::printf("elapsed time %d works is empty, stop trigger...",
                 elapsed_time_);
        TimerTrigger::Stop();
        ::printf("finished\n");
        elapsed_time_ = 0;
    }
    ::printf("elapsed time %d finished\n", elapsed_time_);
}
