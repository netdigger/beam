/* Copyright ©2016 All right reserved*/

#ifndef __MOCK_TASK_H__
#define __MOCK_TASK_H__

#include <gmock/gmock.h>
#include "beam/task.h"
#include "wait.h"

using namespace beam;
class MockTask : public Task {
   public:
    MOCK_METHOD1(Run, void(void*));

    void Wait(void* arg) {
        int msec = *static_cast<int*>(arg);
        ::Wait(msec);
    }
};

#endif
