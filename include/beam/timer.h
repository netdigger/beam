/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_H__
#define __TIMER_H__
namespace beam {
class Task;
class Timer {
   public:
    virtual ~Timer(){};

    static Timer* DoOnce(Task&, void*, int);
    static Timer* DoRepeat(Task&, void*, int);
    static void Cancel(Timer*);
};
}  // namespace beam
#endif
