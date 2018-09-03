/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_TRIGGER_H__
#define __TIMER_TRIGGER_H__
#include <beam/task.h>
#include <signal.h>
#include <time.h>

namespace beam {
class Task;
class Thread;
class TimerTrigger : public Task {
   public:
    TimerTrigger(Task&, void*);
    virtual ~TimerTrigger();

   private:
    Task& task_;
    void* args_;
    Thread* thread_;

    timer_t timer_id_;
    sigset_t old_sigset_;
    struct sigevent sigevent_;
    struct itimerspec itime_;

    void Run(void*);
    int init();
};
}  // namespace beam
#endif
