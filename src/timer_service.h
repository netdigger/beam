/* Copyright ©2018 All right reserved, Author: netdigger*/

#ifndef __TIMER_SERVICE_H__
#define __TIMER_SERVICE_H__

#include <set>
#include "beam/mutex.h"
#include "beam/task.h"

namespace beam {
class Timer;
class TimerWorker;
class TimerTrigger;
class TimerService : public Task {
   public:
    virtual ~TimerService();
    static Timer* Add(Task& task, void* args, int time, bool once) {
        return instance_.DoAdd(task, args, time, once);
    };
    static void Cancel(Timer* timer) { instance_.DoCancel(timer); }

   private:
    static TimerService instance_;
    struct TimerInfo {
        TimerWorker* worker;
        int circle_time;
        int trigger_time;
        bool operator<(const TimerInfo& info) const {
            if (this->trigger_time == info.trigger_time) {
                return this->worker < info.worker;
            }
            return this->trigger_time < info.trigger_time;
        }
    };

    int elapsed_time_;
    TimerTrigger* trigger_;

    Mutex mutex_;
    std::set<TimerInfo> workers_;

    TimerService();
    Timer* DoAdd(Task&, void*, int, bool);
    void DoCancel(Timer*);
    void Run(void*);
};
}  // namespace beam
#endif
