cmake_minimum_required(VERSION 3.20)
project(deq)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")
set(CMAKE_CXX_STANDARD 17)

add_executable(queue queue.cpp)
