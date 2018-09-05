/* Copyright ©2016 All right reserved*/

#ifndef __THREAD_H__
#define __THREAD_H__

namespace beam {
class Task;
class Thread {
   public:
    virtual ~Thread(){};
    virtual bool operator==(const Thread&) const = 0;

    virtual int Stop() = 0;
    virtual int Join() = 0;

    static Thread* Start(Task&, void*);
};
}  // namespace beam
#endif
