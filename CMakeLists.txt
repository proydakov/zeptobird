project(zeptobird)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra -pedantic-errors -fno-rtti -fno-exceptions -D_GLIBCXX_USE_CXX11_ABI=1")

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if(supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "IPO is not supported: ${error}")
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
    #SET(CMAKE_BUILD_TYPE Release)
ENDIF()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/shared)

add_subdirectory(shared)

if(CMAKE_CROSSCOMPILING)
    add_subdirectory(platforms/html5)
else()
    add_subdirectory(test)
    add_subdirectory(platforms/sdl2)
endif()

# build info
SET(BUILD_INFO_BAR "====================================================================================")
SET(NOOP_STRING "")

MESSAGE(STATUS ${BUILD_INFO_BAR})
MESSAGE(STATUS "Summary of the build:")
MESSAGE(STATUS ${BUILD_INFO_BAR})
MESSAGE(STATUS "GENERATOR:    ${CMAKE_GENERATOR}")
MESSAGE(STATUS "C_COMPILER:   ${CMAKE_C_COMPILER} [${CMAKE_C_COMPILER_ID}-${CMAKE_C_COMPILER_VERSION}]")
MESSAGE(STATUS "CXX_COMPILER: ${CMAKE_CXX_COMPILER} [${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}]")
MESSAGE(STATUS "LINKER:       ${CMAKE_LINKER}")
MESSAGE(STATUS "")
MESSAGE(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "")
MESSAGE(STATUS "Build type : ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS ${BUILD_INFO_BAR})
MESSAGE(STATUS ${NOOP_STRING})
