/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_H__
#define __THREAD_H__

#include <beam/task.h>

class Thread {
   public:
    virtual ~Thread(){};

    virtual int Stop() = 0;
    virtual int Join() = 0;

    static Thread* Run(Task&, void*);
};
#endif
