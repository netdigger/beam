/* Copyright ©2016 All right reserved*/

#include <beam/thread.h>
#include "thread_pool.h"

Thread* Thread::Run(Task& task, void* args) {
    return ThreadPool::Schedule(task, args);
}
