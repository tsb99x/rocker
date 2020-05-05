add_library(tokenizer tokenizer.c)
target_link_libraries(tokenizer str_pool node_pool status string_utils)
target_include_directories(tokenizer PUBLIC include)

add_executable(tokenizer_test tokenizer_test.c)
target_link_libraries(tokenizer_test tokenizer makro)
add_test(tokenizer tokenizer_test)
