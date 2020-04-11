cmake_minimum_required(VERSION 3.7)
project(rocker C)
set(CMAKE_C_STANDARD 11)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
if(MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(${PROJECT_NAME} 
    src/main.c src/node_pool.c src/str_pool.c src/string_utils.c src/printer.c)

enable_testing()
add_executable(string_utils_test
    src/string_utils.c
    src/string_utils_test.c)
add_test(string_utils string_utils_test)

add_executable(printer_test
    src/printer.c
    src/node_pool.c
    src/printer_test.c)
add_test(printer printer_test)
