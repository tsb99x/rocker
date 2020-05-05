#pragma once

#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x)                                                              \
        (void) x

#define ARRLEN(x)                                                              \
        (sizeof(x) / sizeof(x[0]))

#define CONCAT(a, b)                                                           \
        a ## b

#define EVAL(x, y)                                                             \
        CONCAT(x, y)

#define PANIC(msg, ...)                                                        \
        do {                                                                   \
                fprintf(stderr, msg, ##__VA_ARGS__);                           \
                exit(EXIT_FAILURE);                                            \
        } while (0)

#define REQUIRE(predicate)                                                     \
        do {                                                                   \
                if (!(predicate)) {                                            \
                        fprintf(stderr,                                        \
                                "Assertion failed: " #predicate ", "           \
                                "file %s, line %d\n", __FILE__, __LINE__);     \
                        exit(EXIT_FAILURE);                                    \
                }                                                              \
        } while (0)
