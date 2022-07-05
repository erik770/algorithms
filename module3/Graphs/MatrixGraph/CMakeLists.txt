add_library(MatrixGraph src/MatrixGraph.cpp)

target_include_directories(MatrixGraph PUBLIC include)
target_link_libraries(MatrixGraph PUBLIC GraphInterface)
