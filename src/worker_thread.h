/* Copyright ©2016 All right reserved*/

#ifndef __WORKER_THREAD_H__
#define __WORKER_THREAD_H__
#include <pthread.h>
#include "beam/mutex.h"
#include "beam/semaphore.h"
#include "beam/thread.h"

class ThreadObserver;
class Task;
class WorkerThread : public Thread {
   public:
    WorkerThread(ThreadObserver*);
    ~WorkerThread();

    int Schedule(Task&, void*);
    int Stop();
    int Join();
    bool IsCanceled() const { return canceled_; };

   private:
    pthread_t thread_;

    void* arg_;
    bool idle_;
    bool canceled_;
    bool deleted_;
    Task* task_;
    ThreadObserver* observer_;

    Semaphore sem_;
    Mutex join_lock_;

    void Execute(void*);
    void* Run();
    void Cleanup();
    static void* RunFunc(void*);
    static void CleanupFunc(void*);
};
#endif
