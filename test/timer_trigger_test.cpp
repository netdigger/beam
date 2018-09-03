/* Copyright ©2016 All right reserved*/

#include "timer_trigger.h"

#include "mock_task.h"
#include "wait.h"

using namespace beam;
using namespace testing;

class TimerTriggerTest : public testing::Test {
   public:
    void SetUp() { trigger_ = new TimerTrigger(task_, &wait_time_); };
    void TearDown() { delete trigger_; };

    int wait_time_ = 10;
    TimerTrigger* trigger_;
    MockTask task_;
};

TEST_F(TimerTriggerTest, Schedule) {
    EXPECT_CALL(task_, Run(&wait_time_)).Times(Between(9, 11));
    Wait(10);
}
