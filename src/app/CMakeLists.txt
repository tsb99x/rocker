add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME}
    makro
    node_pool
    printer
    status
    str_pool
    string_utils
    tokenizer)
