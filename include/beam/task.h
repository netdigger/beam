/* Copyright ©2016 All right reserved*/

#ifndef __TASK_H__
#define __TASK_H__
class Task {
public:
	virtual ~Task(){};
	virtual void Execute(void*) = 0;
};
#endif

