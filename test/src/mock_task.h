/* Copyright ©2016 All right reserved*/

#ifndef __MOCK_TASK_H__
#define __MOCK_TASK_H__

#include <beam/task.h>

class MockTask : public Task {
public:
	MOCK_METHOD1(Execute, void(void*));
};

#endif 

