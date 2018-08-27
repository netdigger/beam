/* Copyright ©2016 All right reserved*/

#include <beam/auto_lock.h>
#include <beam/locker.h>
using namespace beam;
AutoLock::AutoLock(Locker& lock) : lock_(lock) { lock_.Lock(); }

AutoLock::~AutoLock() { lock_.Unlock(); }
