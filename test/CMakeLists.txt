cmake_minimum_required (VERSION 2.8)
project (beamut)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/../include 
	${PROJECT_SOURCE_DIR}/../src
	${PROJECT_SOURCE_DIR}/../lib/gtest/googlemock/include
	${PROJECT_SOURCE_DIR}/../lib/gtest/googletest/include
	${PROJECT_BINARY_DIR}
)
set(CMAKE_CXX_FLAGS "-g -Werror -Wall")

# Test
add_executable(beamut ${DIR_SRCS})
target_link_libraries(beamut gmock beam)
