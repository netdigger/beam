/* Copyright ©2016 All right reserved*/

#include <beam/object_pool.h>
#include <gtest/gtest.h>

using namespace beam;
struct ObjectPoolTestStruct {
    int a;
};

TEST(ObjectPoolTest, NewAndDelete) {
    ObjectPool<ObjectPoolTestStruct>& pool =
        ObjectPool<ObjectPoolTestStruct>::GetInstance();

    ObjectPoolTestStruct* data = pool.New();
    EXPECT_FALSE(NULL == data);

    pool.Delete(data);
    ObjectPoolTestStruct* data1 = pool.New();
    EXPECT_TRUE(data == data1);
}
