/* Copyright ©2018 All right reserved*/

class WorkerThread;
class ThreadObserver {
   public:
    virtual ~ThreadObserver(){};

    virtual void OnFinished(WorkerThread*) = 0;
};
