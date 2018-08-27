/* Copyright ©2016 All right reserved*/

#include <beam/semaphore.h>

using namespace beam;
Semaphore::Semaphore(int value) {
    if (value < 0) value = 0;
    ::sem_init(&sem_, 0, value);
}

Semaphore::~Semaphore() { ::sem_destroy(&sem_); }
int Semaphore::Wait() { return ::sem_wait(&sem_); }
int Semaphore::Post() { return ::sem_post(&sem_); }
