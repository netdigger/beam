/* Copyright ©2018 All right reserved, Author: netdigger*/

#include "timer_worker.h"
using namespace beam;

int TimerWorker::Schedule(Type, Task&, void*) {
    int rst = timer_create(SIGEV_THREAD, &sigevent_, &timer_);
    return rst;
}
int TimerWorker::Stop() { return 0; }
Timer::Status TimerWorker::GetStatus() { return kStopped; }
