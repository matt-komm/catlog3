cmake_minimum_required (VERSION 2.8)

project (catlog)
set(CMAKE_CXX_FLAGS "-Wextra -Wall -pedantic -std=c++0x")

include_directories(${CMAKE_PROJECT_SOURCE_DIR})

add_library(catlog 
    LogRecord.cpp
    Logger.cpp
    LogFactory.cpp
    LogLevel.cpp
)

add_executable(catlog-test
    test.cpp
)
target_link_libraries(catlog-test catlog)
