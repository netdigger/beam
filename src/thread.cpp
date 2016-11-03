/* Copyright ©2016 All right reserved*/

#include <beam/thread.h>

Thread::Thread(Task* task, void* args): task_(task), args_(args) {
}

Thread::~Thread(){
	Stop();
}

int Thread::Start() {
	if (NULL == task_) return -1;
	return ::pthread_create(&thread_, NULL, Func, this);
}

int Thread::Stop() {
	return ::pthread_cancel(thread_);
}

int Thread::Join() {
	return ::pthread_join(thread_, NULL);
}

void* Thread::Func(void* arg) {
	Thread* thread = static_cast<Thread*>(arg);
	Task* task = thread->task_;
	if (NULL == task) return NULL;
	task->Execute(thread->args_);
}
