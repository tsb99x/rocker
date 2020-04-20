add_executable(${PROJECT_NAME}
    main.c
        node_pool.c
        str_pool.c
        string_utils.c
        printer.c
        tokenizer.c
        status.c)

add_executable(string_utils_test
    string_utils_test.c
        string_utils.c)
add_test(string_utils string_utils_test)

add_executable(printer_test
    printer_test.c
        printer.c
        node_pool.c)
add_test(printer printer_test)

add_executable(tokenizer_test
    tokenizer_test.c
        tokenizer.c
        str_pool.c
        node_pool.c
        string_utils.c)
add_test(tokenizer tokenizer_test)
