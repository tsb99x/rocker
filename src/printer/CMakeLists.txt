add_library(printer printer.c)
target_link_libraries(printer node_pool)
target_include_directories(printer PUBLIC include)

add_executable(printer_test printer_test.c)
target_link_libraries(printer_test printer)
add_test(printer printer_test)
