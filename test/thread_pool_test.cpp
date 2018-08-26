/* Copyright ©2016 All right reserved*/

#include "thread_pool.h"
#include "beam/thread.h"

#include "mock_task.h"
#include "wait.h"

using testing::Invoke;

class ThreadPoolTest : public testing::Test {
   public:
    void SetUp(){};
    void TearDown(){};

    int wait_time_ = 5;
    MockTask task_;
};

TEST_F(ThreadPoolTest, ScheduleSequence) {
    EXPECT_CALL(task_, Execute(&wait_time_)).Times(2);

    Thread* thread_1 = ThreadPool::Schedule(task_, &wait_time_);
    thread_1->Join();
    Thread* thread_2 = ThreadPool::Schedule(task_, &wait_time_);
    thread_2->Join();
    EXPECT_EQ(thread_1, thread_2);
}

TEST_F(ThreadPoolTest, ScheduleParalleles) {
    EXPECT_CALL(task_, Execute(&wait_time_))
        .Times(2)
        .WillOnce(Invoke(&task_, &MockTask::Wait));

    Thread* thread_1 = ThreadPool::Schedule(task_, &wait_time_);
    Thread* thread_2 = ThreadPool::Schedule(task_, &wait_time_);
    EXPECT_FALSE(thread_1 == thread_2);
    thread_1->Join();
}
