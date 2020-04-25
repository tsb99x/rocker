cmake_minimum_required(VERSION 3.10)
project(rocker LANGUAGES C)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
if(MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

enable_testing()

add_subdirectory(src)
