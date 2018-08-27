/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_MANAGER_H__
#define __TIMER_MANAGER_H__
#include "beam/timer.h"
namespace beam {
class TimerManager {
   public:
    static Timer* Schedule(Timer::Type, Task&, void*);
};
}  // namespace beam
#endif
