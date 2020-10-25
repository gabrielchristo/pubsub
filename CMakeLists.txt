cmake_minimum_required(VERSION 3.5)

project(pub-sub LANGUAGES CXX)

# compile config
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# gtest and pthread libs
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(headers
definitions.h
dispatcher.h
)

set(source
dispatcher.cpp
)

# main executable
add_executable(${PROJECT_NAME} ${source} ${headers} main.cpp)

# unit tests executable
add_executable(${PROJECT_NAME}-test ${source} ${headers} test/tests.cpp)
target_link_libraries(${PROJECT_NAME}-test ${GTEST_BOTH_LIBRARIES} Threads::Threads)
