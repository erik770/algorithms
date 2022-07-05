cmake_minimum_required(VERSION 3.21)
project(Graphs)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(GraphInterface)
add_subdirectory(SetGraph)
add_subdirectory(ListGraph)
add_subdirectory(MatrixGraph)
add_subdirectory(ArcGraph)

add_executable(Graphs main.cpp)
target_link_libraries(Graphs PUBLIC SetGraph ListGraph MatrixGraph ArcGraph)