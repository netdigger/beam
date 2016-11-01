/* Copyright ©2015 All right reserved*/

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <semaphore.h>

class Semaphore {
public:
	Semaphore(int value = 0);
	~Semaphore();

	int Wait();
	int Post();
private:
	sem_t sem_;
};
#endif
