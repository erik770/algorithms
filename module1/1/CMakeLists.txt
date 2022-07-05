cmake_minimum_required(VERSION 3.20)
project(bit)

add_compile_options(-Werror -Wall -Wextra -Wpedantic)
set(CMAKE_CXX_STANDARD 14)

add_executable(bit
        bit.cpp)
