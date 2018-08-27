/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_H__
#define __THREAD_H__

#include <beam/task.h>

namespace beam {
class Thread {
   public:
    virtual ~Thread(){};

    virtual int Stop() = 0;
    virtual int Join() = 0;

    static Thread* Run(Task&, void*);
};
}  // namespace beam
#endif
