cmake_minimum_required (VERSION 2.8)
project (libbeam)

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/beam_config.h.in"
    "${PROJECT_BINARY_DIR}/beam_config.h"
)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
add_library(beam SHARED ${DIR_SRCS})
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/include 
	${PROJECT_SOURCE_DIR}/lib/gtest/googlemock/include
	${PROJECT_SOURCE_DIR}/lib/gtest/googletest/include
	${PROJECT_BINARY_DIR}
)
set(CMAKE_CXX_FLAGS "-Werror -Wall")

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/gtest)

# Test
enable_testing()
aux_source_directory(${PROJECT_SOURCE_DIR}/test TEST_SRCS)
add_executable(beamut ${TEST_SRCS})
target_link_libraries(beamut gmock beam)
add_test(unitTest beamut)
