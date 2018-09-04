CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(SRCS
    auto_lock.cpp
    mutex.cpp
    semaphore.cpp
    thread.cpp
    thread_pool.cpp
    timer.cpp
    timer_service.cpp
    timer_trigger.cpp
    timer_worker.cpp
    worker_thread.cpp
    )

ADD_LIBRARY(${PRJ_NAME} SHARED ${SRCS})
TARGET_LINK_LIBRARIES(${PRJ_NAME} rt)
SET_TARGET_PROPERTIES(${PRJ_NAME} PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}
    SOVERSION ${VERSION_MAJOR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# install
INSTALL(TARGETS ${PRJ_NAME}
    LIBRARY DESTINATION lib
    )
