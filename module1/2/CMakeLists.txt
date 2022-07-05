cmake_minimum_required(VERSION 3.20)
project(binary_search)

add_compile_options(-Werror -Wall -Wextra -Wpedantic)
set(CMAKE_CXX_STANDARD 14)

add_executable(binary
        binary.cpp)
