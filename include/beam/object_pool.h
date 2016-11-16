/* Copyright ©2016 All right reserved*/

#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__
#include <stack>
#include <beam/mutex.h>
#include <beam/auto_lock.h>

template<class T>
class ObjectPool {
public:
	virtual ~ObjectPool() {
		while (!objs_.empty()) {
			delete objs_.top();
			objs_.pop();
		}
	}

	T* New() {
		T* data;
		AutoLock lock(mutex_);
		if (!objs_.empty()) {
			data = objs_.top();
			objs_.pop();
		} else data = new T;

		return data;
	};

	void Delete(T* data) {
		if (NULL == data) return;
		AutoLock lock(mutex_);
		objs_.push(data);
	};

	static ObjectPool<T>& GetInstance() {return instance_;};
private:
		ObjectPool() {};
		ObjectPool(const ObjectPool<T>&) {};
		ObjectPool& operator =(const ObjectPool<T>) {};

		static ObjectPool<T> instance_;

		Mutex mutex_;
		std::stack<T*> objs_;
};

template<class T>
ObjectPool<T> ObjectPool<T>::instance_;
#endif

