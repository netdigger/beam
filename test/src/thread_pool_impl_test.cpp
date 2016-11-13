/* Copyright ©2016 All right reserved*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "thread_pool_impl.h"
#include "wait.h"
#include "mock_task.h"

TEST(ThreadPoolImplTest, Schedule) {
	MockTask task; 
	EXPECT_CALL(task, Execute(NULL)).Times(1);  

	ThreadPoolImpl pool; 
	pool.Schedule(task, NULL);;
	Wait(10);

	EXPECT_EQ(1, pool.count_);
	int count = pool.idles_.size();
	EXPECT_EQ(1, count);
	count = pool.busys_.size();
	EXPECT_EQ(0, count);

	MockTask task1; 
	EXPECT_CALL(task1, Execute(&task)).Times(1);  
	pool.Schedule(task1, &task);;
	Wait(30);

	EXPECT_EQ(1, pool.count_);
	count = pool.idles_.size();
	EXPECT_EQ(1, count);
	count = pool.busys_.size();
	EXPECT_EQ(0, count);
}
