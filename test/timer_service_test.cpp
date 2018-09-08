/* Copyright ©2016 All right reserved*/

#include "timer_service.h"

#include "mock_task.h"
#include "mock_thread_observer.h"
#include "wait.h"

using namespace beam;
using namespace testing;

class TimerServiceTest : public testing::Test {
   public:
    void SetUp() {}
    void TearDown(){};

    int wait_time_ = 5;
    int cycle_time = 2;
    MockTask task_;
};

TEST_F(TimerServiceTest, AddOnce) {
    TimerService::Add(task_, &wait_time_, 1, true);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(1);
    Wait(4);
}

TEST_F(TimerServiceTest, Repeat) {
    Timer* timer = TimerService::Add(task_, &wait_time_, 2, false);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(Between(2, 3));
    Wait(5);
    TimerService::Cancel(timer);
}

TEST_F(TimerServiceTest, AddOnceMultiple) {
    TimerService::Add(task_, &wait_time_, 2, true);
    TimerService::Add(task_, &wait_time_, 1, true);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(2);
    Wait(5);
}

TEST_F(TimerServiceTest, RepeatMultiple) {
    MockTask task;
    Timer* timer_1 = TimerService::Add(task_, &wait_time_, 2, false);
    Timer* timer_2 = TimerService::Add(task, &wait_time_, 1, false);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(Between(2, 3));
    EXPECT_CALL(task, Run(&wait_time_)).Times(Between(4, 5));
    Wait(5);
    TimerService::Cancel(timer_1);
    TimerService::Cancel(timer_2);
}

TEST_F(TimerServiceTest, CancelRepeated) {
    Timer* timer = TimerService::Add(task_, &wait_time_, 4, false);
    EXPECT_CALL(task_, Run(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));

    Wait(6);
    TimerService::Cancel(timer);
}
