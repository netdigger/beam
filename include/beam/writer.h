/* Copyright ©2016 All right reserved*/

#ifndef __WRITER_H__
#define __WRITER_H__

#include <unistd.h>

class Writer {
public:
	virtual ~Writer() {};

	virtual ssize_t Write(const void* buffer, size_t size);
};
#endif

