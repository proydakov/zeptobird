project(zeptobird)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11")
#set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(math)
add_subdirectory(phys)
add_subdirectory(demo)
