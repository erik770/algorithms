add_library(ListGraph src/ListGraph.cpp)

target_include_directories(ListGraph PUBLIC include)
target_link_libraries(ListGraph PUBLIC GraphInterface)
