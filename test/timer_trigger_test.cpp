/* Copyright ©2016 All right reserved*/

#include "timer_trigger.h"

#include "mock_task.h"
#include "wait.h"

using namespace beam;
using namespace testing;

class TimerTriggerTest : public testing::Test {
   public:
    void SetUp(){};
    void TearDown(){};

    int wait_time_ = 10;
    MockTask task_;
};

TEST_F(TimerTriggerTest, StartAndStop) {
    TimerTrigger::Start(task_, &wait_time_);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(Between(9, 11));
    Wait(10);
    TimerTrigger::Stop();
}

TEST_F(TimerTriggerTest, StartAndStopMultiple) {
    TimerTrigger::Start(task_, &wait_time_);
    EXPECT_CALL(task_, Run(&wait_time_)).Times(Between(9, 11));
    Wait(10);
    TimerTrigger::Stop();

    MockTask task;
    TimerTrigger::Start(task, &wait_time_);
    EXPECT_CALL(task, Run(&wait_time_)).Times(Between(9, 11));
    Wait(10);
    TimerTrigger::Stop();
}
