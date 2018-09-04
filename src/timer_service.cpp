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
    AutoLock lock(mutex_);
    if (workers_.size() == 0) {
        TimerTrigger::Start(*this, NULL);
        elapsed_time_ = 0;
    }

    if (time < 0) time = 0;
    TimerWorker* timer = new TimerWorker(task, args, once);
    TimerInfo info = {timer, time, time + elapsed_time_};
    workers_.insert(info);
    return NULL;
}

void TimerService::DoCancel(Timer* timer) {
    AutoLock lock(mutex_);
    for (auto it = workers_.begin(); it != workers_.end(); ++it) {
        if (it->worker == timer) {
            it->worker->Cancel();
            delete it->worker;
            workers_.erase(it);
            return;
        }
    }
}

void TimerService::Run(void*) {
    AutoLock lock(mutex_);
    elapsed_time_++;
    TimerInfo info;
    auto it = workers_.begin();
    while (it != workers_.end()) {
        if (it->worker->GetStatus() == TimerWorker::kCancelled) {
            delete it->worker;
            it = workers_.erase(it);
            continue;
        }

        if (elapsed_time_ >= it->trigger_time) {
            it->worker->Schedule();
            info = *it;
            info.trigger_time = info.circle_time + elapsed_time_;
            it = workers_.erase(it);
            workers_.insert(info);
        } else
            break;
    }

    if (workers_.empty()) {
        TimerTrigger::Stop();
    }
}
