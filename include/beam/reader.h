/* Copyright ©2016 All right reserved*/

#ifndef __READER_H__
#define __READER_H__

#include <unistd.h>

namespace beam {
class Reader {
   public:
    virtual ~Reader(){};

    virtual ssize_t Read(void* buffer, size_t size);
};
}  // namespace beam
#endif
