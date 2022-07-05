cmake_minimum_required(VERSION 3.20)
project(heap_merge)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")
set(CMAKE_CXX_STANDARD 17)

add_executable(heap_merge heap_merge.cpp)