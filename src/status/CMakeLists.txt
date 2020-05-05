add_library(status status.c)
target_link_libraries(status makro)
target_include_directories(status PUBLIC include)
