/* Copyright ©2016 All right reserved*/

#ifndef __LOCKER_H__
#define __LOCKER_H__
namespace beam {
class Locker {
   public:
    virtual ~Locker(){};

    virtual int Lock() = 0;
    virtual int Unlock() = 0;
};
}  // namespace beam
#endif
