/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "beam/timer.h"
#include <stdio.h>
#include "timer_manager.h"

using namespace beam;
Timer* Timer::Start(Timer::Type type, Task& task, void* args) {
    return TimerManager::Schedule(type, task, args);
}
