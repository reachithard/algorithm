cmake_minimum_required(VERSION 3.12)

project(algorithm)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

option(BUILD_TESTS "Build unit tests." ON)
option(DOWNLOAD_THIRDPARTY "Download thirdparty." ON)

# 设置基础变量
SET(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# 链接interface 便于开发
INCLUDE(cmake/interface.cmake)

set(ALGORITHM_MAJOR_VERSION 0)
set(ALGORITHM_MINOR_VERSION 0)
set(ALGORITHM_PATCH_VERSION 1)
set(ALGORITHM_VERSION
    ${ALGORITHM_MAJOR_VERSION}.${ALGORITHM_MINOR_VERSION}.${ALGORITHM_PATCH_VERSION})
set(ALGORITHM_VERSION_STRING "${ALGORITHM_VERSION}")

if(DOWNLOAD_THIRDPARTY) 
include(cmake/thirdparty.cmake)
endif()

add_subdirectory(carl)