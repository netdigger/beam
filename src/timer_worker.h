/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_WORKER_H__
#define __TIMER_WORKER_H__

#include "beam/mutex.h"
#include "beam/task.h"
#include "beam/timer.h"

namespace beam {
class Thread;
class TimerWorker : public Timer, public Task {
   public:
    TimerWorker(Task&, void*, bool);
    virtual ~TimerWorker(){};

    enum Status { kWaiting = 1, kRunning, kCancelled };

    Status Schedule();
    Status GetStatus() { return status_; };

    // Timer
    int Cancel();
    // Task
    void Run(void*);

   private:
    Mutex mutex_;
    Task& task_;
    void* args_;
    Thread* thread_;
    Status status_;
    bool run_once_;
};
}  // namespace beam
#endif
