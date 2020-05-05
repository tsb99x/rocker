add_library(str_pool str_pool.c)
target_link_libraries(str_pool status templates)
target_include_directories(str_pool PUBLIC include)
