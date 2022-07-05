add_library(SetGraph src/SetGraph.cpp)

target_include_directories(SetGraph PUBLIC include)
target_link_libraries(SetGraph PUBLIC GraphInterface)
