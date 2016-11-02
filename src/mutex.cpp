/* Copyright ©2016 All right reserved*/

#include <beam/mutex.h>

Mutex::Mutex() {
	::pthread_mutex_init(&mutex_, 0);
}

Mutex::~Mutex() {
	::pthread_mutex_destroy(&mutex_);
}

int Mutex::Lock() {
	return ::pthread_mutex_lock(&mutex_);
}

int Mutex::Unlock() {
	return ::pthread_mutex_unlock(&mutex_);
}
