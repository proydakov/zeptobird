project(zeptobird)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")
set(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/shared)

add_subdirectory(shared)

if(CMAKE_CROSSCOMPILING)
    add_subdirectory(platforms/html5)
else()
    add_subdirectory(test)
    add_subdirectory(platforms/qt5)
endif()
