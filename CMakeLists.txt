project(zeptobird)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11")
#set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/shared)

add_subdirectory(shared)
add_subdirectory(test)

if(UNIX AND NOT APPLE)
    SET(ABS_RES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shared/resources)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/resource.h ${CMAKE_CURRENT_SOURCE_DIR}/linux/generated_resource.h)
    add_subdirectory(linux)
endif()
