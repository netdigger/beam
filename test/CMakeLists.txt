CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
MESSAGE(STATUS ${CMAKE_MODULE_PATH})

SET(SRCS
	main.cpp
	object_pool_test.cpp
    timer_service_test.cpp
    timer_trigger_test.cpp
    timer_worker_test.cpp
    thread_pool_test.cpp
    thread_test.cpp
	worker_thread_test.cpp
	wait.cpp
)

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/src
)
SET(THREADS_PREFER_PTHREAD_FLAG ON)
FIND_PACKAGE(GMock REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

# Test
SET(UT_NAME ${PRJ_NAME}_test)
ADD_EXECUTABLE(${UT_NAME} ${SRCS})
TARGET_LINK_LIBRARIES(${UT_NAME} Threads::Threads GMock::GMock 
	${GTEST_LIBRARIES} ${PRJ_NAME}
)

SET_TARGET_PROPERTIES(${UT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
