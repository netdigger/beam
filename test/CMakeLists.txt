CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(SRCS
	src/main.cpp
	src/object_pool_test.cpp
	src/thread_pool_impl_test.cpp
	src/wait.cpp
)

MESSAGE(STATUS "dir is ${PROJECT_SOURCE_DIR}")

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/lib/gtest/googlemock/include
	${PROJECT_SOURCE_DIR}/lib/gtest/googletest/include
)
SET(CMAKE_CXX_FLAGS "-g -Werror -Wall")

# Test
ADD_EXECUTABLE(${PRJ_NAME}_test ${SRCS})
TARGET_LINK_LIBRARIES(${PRJ_NAME}_test gmock beam)

SET_TARGET_PROPERTIES(${PRJ_NAME}_test PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
