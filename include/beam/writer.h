/* Copyright ©2016 All right reserved*/

#ifndef __WRITER_H__
#define __WRITER_H__

#include <unistd.h>

namespace beam {
class Writer {
   public:
    virtual ~Writer(){};

    virtual ssize_t Write(const void* buffer, size_t size);
};
}  // namespace beam
#endif
