/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <beam/mutex.h>
#include <list>
#include <stack>
#include "thread_observer.h"
#include "worker_thread.h"

namespace beam {
class Task;

class ThreadPool : public ThreadObserver {
   public:
    ~ThreadPool();

    /*
     * Schedule a task;
     * @param task The Scheduled task;
     * @args Arguments used in task;
     */
    static Thread* Schedule(Task& task, void* arg) {
        return instance_.DoSchedule(task, arg);
    };

   private:
    static ThreadPool instance_;

    Mutex mutex_;
    std::stack<WorkerThread*> idles_;
    std::list<WorkerThread*> busys_;

    ThreadPool(){};
    ThreadPool(ThreadPool&){};
    Thread* DoSchedule(Task&, void*);

    // Thread Observer
    void OnFinished(WorkerThread*);
};
}  // namespace beam
#endif
