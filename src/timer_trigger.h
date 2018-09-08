/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_TRIGGER_H__
#define __TIMER_TRIGGER_H__
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "beam/semaphore.h"
#include "beam/task.h"

namespace beam {
class Task;
class Thread;
class TimerTrigger : public Task {
   public:
    virtual ~TimerTrigger();
    static void Start(Task& task, void* args) {
        instance_.DoStart(task, args);
    };
    static void Stop() { instance_.DoStop(); };

   private:
    static TimerTrigger instance_;
    Task* task_;
    void* args_;
    Thread* thread_;

    bool run_;
    timer_t timer_id_;
    pthread_t thread_id_;
    sigset_t old_sigset_;
    struct sigevent sigevent_;
    struct itimerspec itime_;
    Semaphore sem_;

    TimerTrigger();
    TimerTrigger(TimerTrigger&){};
    void DoStart(Task&, void*);
    void DoStop();
    void Run(void*);
    int init();
    static void HandleSignal(int){};
};
}  // namespace beam
#endif
