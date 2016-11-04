/* Copyright ©2016 All right reserved*/

#ifndef __AUTO_LOCK_H__
#define __AUTO_LOCK_H__

class Locker;
class AutoLock {
public:
	AutoLock(Locker&);
	~AutoLock();
private:
	Locker& lock_;
};
#endif
