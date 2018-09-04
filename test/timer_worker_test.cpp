/* Copyright ©2016 All right reserved*/

#include "timer_worker.h"

#include "mock_task.h"
#include "mock_thread_observer.h"
#include "wait.h"

using namespace beam;
using testing::Invoke;

class TimerWorkerTest : public testing::Test {
   public:
    void SetUp() {}
    void TearDown(){};

    int wait_time_ = 5;
    MockTask task_;
};

TEST_F(TimerWorkerTest, Schedule) {
    TimerWorker worker(task_, &wait_time_, true);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(1);

    EXPECT_EQ(TimerWorker::kWaiting, worker.GetStatus());
    EXPECT_EQ(TimerWorker::kRunning, worker.Schedule());
    Wait(2);
    EXPECT_EQ(TimerWorker::kCancelled, worker.GetStatus());
    EXPECT_EQ(TimerWorker::kCancelled, worker.Schedule());
}

TEST_F(TimerWorkerTest, ScheduleRepeat) {
    TimerWorker worker(task_, &wait_time_, false);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(1);

    EXPECT_EQ(TimerWorker::kWaiting, worker.GetStatus());
    EXPECT_EQ(TimerWorker::kRunning, worker.Schedule());
    Wait(2);
    EXPECT_EQ(TimerWorker::kWaiting, worker.GetStatus());
    worker.Cancel();
    EXPECT_EQ(TimerWorker::kCancelled, worker.GetStatus());
}

TEST_F(TimerWorkerTest, CancelBeforeSchedule) {
    TimerWorker worker(task_, &wait_time_, true);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(0);
    worker.Cancel();
    EXPECT_EQ(TimerWorker::kCancelled, worker.GetStatus());
}

TEST_F(TimerWorkerTest, CancelAfterSchedule) {
    TimerWorker worker(task_, &wait_time_, true);
    EXPECT_CALL(task_, Run(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));

    EXPECT_EQ(TimerWorker::kRunning, worker.Schedule());
    Wait(2);
    EXPECT_EQ(TimerWorker::kRunning, worker.GetStatus());
    worker.Cancel();
    EXPECT_EQ(TimerWorker::kCancelled, worker.GetStatus());
    EXPECT_EQ(TimerWorker::kCancelled, worker.Schedule());
}
