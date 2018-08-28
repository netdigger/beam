/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_WORKER_H__
#define __TIMER_WORKER_H__

#include <signal.h>
#include <time.h>
#include "beam/timer.h"

namespace beam {
class TimerWorker : public Timer {
   public:
    virtual ~TimerWorker(){};

    int Schedule(Type, Task&, void*);
    int Stop();
    Status GetStatus();

   private:
    timer_t timer_;
    Task* task_;
    void* args_;
    Type type_;
    struct sigevent sigevent_;
};
}  // namespace beam
#endif
