/* Copyright ©2018 All right reserved*/

class WorkerThread;
class ThreadObserver {
public:
	virtual ~ThreadObserver() {};

	virtual void OnTaskFinished(WorkerThread*) = 0;
	virtual void OnCanceled(WorkerThread*) = 0;
};

