cmake_minimum_required(VERSION 3.5)

project(pub-sub LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(headers
definitions.h
dispatcher.h
)

set(source
main.cpp
dispatcher.cpp
)

add_executable(${PROJECT_NAME} ${source} ${headers})
