add_library(node_pool node_pool.c)
target_link_libraries(node_pool makro templates status)
target_include_directories(node_pool PUBLIC include)
