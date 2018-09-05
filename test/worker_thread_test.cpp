/* Copyright ©2016 All right reserved*/

#include "worker_thread.h"

#include "mock_task.h"
#include "mock_thread_observer.h"
#include "wait.h"

using namespace beam;
using testing::Invoke;

class WorkerThreadTest : public testing::Test {
   public:
    void SetUp() { thread_ = new WorkerThread(&ob_); };
    void TearDown() { delete thread_; };

    int wait_time_ = 10;
    WorkerThread* thread_;
    MockTask task_;
    MockThreadObserver ob_;
};

TEST_F(WorkerThreadTest, OperatorEqual) {
    WorkerThread thread(&ob_);

    EXPECT_TRUE(*thread_ == *thread_);
    EXPECT_FALSE(*thread_ == thread);
    EXPECT_TRUE(thread == thread);
    EXPECT_FALSE(thread == *thread_);
}

TEST_F(WorkerThreadTest, Schedule) {
    EXPECT_CALL(task_, Run(&wait_time_)).Times(2);
    EXPECT_CALL(ob_, OnFinished(thread_)).Times(2);

    thread_->Schedule(task_, &wait_time_);
    thread_->Join();
    thread_->Schedule(task_, &wait_time_);
    thread_->Join();
}

TEST_F(WorkerThreadTest, Cancel) {
    EXPECT_CALL(task_, Run(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));
    EXPECT_CALL(ob_, OnFinished(thread_)).Times(1);

    thread_->Schedule(task_, &wait_time_);
    Wait(3);  // Sometimes Workthread does not start to do task.
    thread_->Stop();
}

TEST_F(WorkerThreadTest, Join) {
    EXPECT_CALL(task_, Run(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));
    EXPECT_CALL(ob_, OnFinished(thread_)).Times(1);

    thread_->Schedule(task_, &wait_time_);
    thread_->Join();
    thread_->Stop();
}
