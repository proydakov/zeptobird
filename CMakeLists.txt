project(zeptobird)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11")
#set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/game)

add_subdirectory(game)
add_subdirectory(test)
