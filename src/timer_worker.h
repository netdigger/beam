/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_WORKER_H__
#define __TIMER_WORKER_H__
#include "beam/timer.h"
namespace beam {
class TimerWorker : public Timer {
   public:
    TimerWorker(Type, Task&, void*);
    virtual ~TimerWorker() {}
    int Stop();
    Status GetStatus();

   private:
    Task* task_;
    void* args_;
    Type type_;
};
}  // namespace beam
#endif
