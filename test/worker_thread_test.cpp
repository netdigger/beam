/* Copyright ©2016 All right reserved*/

#include "worker_thread.h"

#include "mock_task.h"
#include "mock_thread_observer.h"
#include "wait.h"

using namespace beam;
using testing::Invoke;

class WorkThreadTest : public testing::Test {
   public:
    void SetUp() { thread_ = new WorkerThread(&ob_); };
    void TearDown() { delete thread_; };

    int wait_time_ = 10;
    WorkerThread* thread_;
    MockTask task_;
    MockThreadObserver ob_;
};

TEST_F(WorkThreadTest, Schedule) {
    EXPECT_CALL(task_, Execute(&wait_time_)).Times(2);
    EXPECT_CALL(ob_, OnFinished(thread_)).Times(2);

    thread_->Schedule(task_, &wait_time_);
    thread_->Join();
    thread_->Schedule(task_, &wait_time_);
    thread_->Join();
}

TEST_F(WorkThreadTest, Cancel) {
    EXPECT_CALL(task_, Execute(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));
    EXPECT_CALL(ob_, OnFinished(thread_)).Times(1);

    thread_->Schedule(task_, &wait_time_);
    Wait(3);  // Sometimes Workthread does not start to do task.
    thread_->Stop();
}

TEST_F(WorkThreadTest, Join) {
    EXPECT_CALL(task_, Execute(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));
    EXPECT_CALL(ob_, OnFinished(thread_)).Times(1);

    thread_->Schedule(task_, &wait_time_);
    thread_->Join();
    thread_->Stop();
}
