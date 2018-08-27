/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_H__
#define __TIMER_H__
namespace beam {
class Task;
class Timer {
   public:
    virtual ~Timer(){};

    enum Type {
        kOnce = 1,  // Task will be execute one time
        kRepeat     // Task is being executed untile removed
    };

    enum Status { kWaiting = 1, kRuning, kStopped };

    virtual int Stop() = 0;
    virtual Status GetStatus() = 0;

    static Timer* Start(Type, Task&, void*);
};
}  // namespace beam
#endif
