CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(PRJ_NAME beam)
PROJECT(lib${PRJ_NAME})

# The version number.
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/version.h.in"
	"${PROJECT_SOURCE_DIR}/include/${PRJ_NAME}/version.h"
)

SET(SRCS
	src/auto_lock.cpp
	src/mutex.cpp
	src/semaphore.cpp
	src/thread.cpp
	src/thread_pool.cpp
	src/thread_pool_impl.cpp
	src/worker_thread.cpp
)

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/include
)

SET(CMAKE_CXX_FLAGS "-Werror -Wall")

ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/lib/gtest)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/test)


ADD_LIBRARY(${PRJ_NAME} SHARED ${SRCS})

# Test
#enable_testing()
#aux_source_directory(${PROJECT_SOURCE_DIR}/test TEST_SRCS)
#add_executable(beamut ${TEST_SRCS})
#target_link_libraries(beamut gmock beam)
#add_test(unitTest beamut)
