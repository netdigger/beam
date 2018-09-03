/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "timer_manager.h"
#include <stdio.h>
#include <unistd.h>
#include "timer_worker.h"

using namespace beam;
TimerManager TimerManager::instance_;
Timer* TimerManager::DoAdd(Task& task, void* args, int time, bool once) {
    if (time < 0) time = 0;
    TimerWorker* timer = new TimerWorker(task, args, once);
    TimerInfo info = {timer, time};
    workers_.insert(info);
    return NULL;
}

void TimerManager::Run(void*) { ::printf("Timer trigger\n"); }
