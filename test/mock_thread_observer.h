/* Copyright ©2016 All right reserved*/

#ifndef __MOCK_THREAT_OBSERVER_H__
#define __MOCK_THREAT_OBSERVER_H__

#include "thread_observer.h"

using namespace beam;
class MockThreadObserver : public ThreadObserver {
   public:
    MOCK_METHOD1(OnFinished, void(WorkerThread*));
};

#endif
