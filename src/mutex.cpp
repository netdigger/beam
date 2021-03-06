/* Copyright ©2016 All right reserved*/

#include <beam/mutex.h>

using namespace beam;
Mutex::Mutex() { ::pthread_mutex_init(&mutex_, 0); }
Mutex::~Mutex() { ::pthread_mutex_destroy(&mutex_); }
int Mutex::Lock() { return ::pthread_mutex_lock(&mutex_); }
int Mutex::Unlock() { return ::pthread_mutex_unlock(&mutex_); }
int Mutex::TryLock() { return ::pthread_mutex_trylock(&mutex_); }
