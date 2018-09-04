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
    virtual ~TimerTrigger();
    static void Start(Task& task, void* args) {
        instance_.DoStart(task, args);
    };
    static void Stop() { instance_.run_ = false; };

   private:
    static TimerTrigger instance_;
    Task* task_;
    void* args_;
    Thread* thread_;

    bool run_;
    timer_t timer_id_;
    sigset_t old_sigset_;
    struct sigevent sigevent_;
    struct itimerspec itime_;

    TimerTrigger(){};
    TimerTrigger(TimerTrigger&){};
    void DoStart(Task&, void*);
    void Run(void*);
    int init();
};
}  // namespace beam
#endif
