/* Copyright ©2016 All right reserved*/

#ifndef __LOCK_H__
#define __LOCK_H__
class Lock {
public:
	virtual ~Lock(){};

	virtual Lock() = 0;
	virtual Unlock() = 0;
};
#endif 
