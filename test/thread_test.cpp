/* Copyright ©2016 All right reserved*/

#include <beam/thread.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mock_task.h"
#include "wait.h"

using namespace beam;
TEST(ThreadTest, Run) {
    MockTask task;
    EXPECT_CALL(task, Execute(NULL)).Times(1);

    Thread* thread = Thread::Start(task, NULL);
    thread->Join();
}
