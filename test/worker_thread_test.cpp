/* Copyright ©2016 All right reserved*/

#include "worker_thread.h"

#include "wait.h"
#include "mock_task.h"
#include "mock_thread_observer.h"

using testing::Invoke;

class WorkThreadTest:  public testing::Test {
public:
    void SetUp() {
        thread_ = new WorkerThread(&ob_);
        thread_->Schedule(task_, &wait_time_); 
    };
    void TearDown() {delete thread_;};

    int wait_time_ = 4;
    WorkerThread* thread_;
	MockTask task_; 
	MockThreadObserver ob_;
};

TEST_F(WorkThreadTest, ScheduleAndStart) {
	EXPECT_CALL(task_, Execute(&wait_time_)).Times(1);  
    EXPECT_CALL(ob_, OnTaskFinished(thread_)).Times(1);
    EXPECT_CALL(ob_, OnCanceled(thread_)).Times(1);

	thread_->Start();
    thread_->Join();
	Wait(1);
}

TEST_F(WorkThreadTest, Cancel) {
    EXPECT_CALL(task_, Execute(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));
    EXPECT_CALL(ob_, OnCanceled(thread_)).Times(1);
    EXPECT_CALL(ob_, OnTaskFinished(thread_)).Times(0);

	thread_->Start();
	Wait(1);
    thread_->Stop();
}

TEST_F(WorkThreadTest, Join) {
    EXPECT_CALL(task_, Execute(&wait_time_))
        .Times(1)
        .WillOnce(Invoke(&task_, &MockTask::Wait));
    EXPECT_CALL(ob_, OnCanceled(thread_)).Times(1);
    EXPECT_CALL(ob_, OnTaskFinished(thread_)).Times(1);

    thread_->Start();
    Wait(1);
    thread_->Join();
}
