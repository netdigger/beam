/* Copyright ©2018 All right reserved*/
#ifndef __THREAD_OBSERVER_H__
#define __THREAD_OBSERVER_H__
namespace beam {
class WorkerThread;
class ThreadObserver {
   public:
    virtual ~ThreadObserver(){};

    virtual void OnFinished(WorkerThread*) = 0;
};
}  // namespace beam
#endif
