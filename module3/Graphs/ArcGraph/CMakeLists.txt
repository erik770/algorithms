add_library(ArcGraph src/ArcGraph.cpp)

target_include_directories(ArcGraph PUBLIC include)
target_link_libraries(ArcGraph PUBLIC GraphInterface)
