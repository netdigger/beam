/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "beam/timer.h"
#include <stdio.h>
#include "timer_manager.h"

using namespace beam;
Timer* Timer::DoOnce(Task& task, void* args, int time) {
    return TimerManager::Add(task, args, time, true);
}

Timer* Timer::DoRepeat(Task& task, void* args, int time) {
    return TimerManager::Add(task, args, time, true);
}
