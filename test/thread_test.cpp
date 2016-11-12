/* Copyright ©2016 All right reserved*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <beam/thread.h>
#include "wait.h"
#include "mock_task.h"

TEST(ThreadTest, AddTask) {
	MockTask task; 
	EXPECT_CALL(task, Execute(NULL)).Times(1);  

	Thread thread(&task, NULL);
	thread.Start();
	Wait(10);
}
