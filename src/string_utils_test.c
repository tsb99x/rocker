#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "string_utils.h"

#define DEFAULT_STRING_SIZE 255

#define REQUIRE(predicate)                                                      \
        do {                                                                    \
                if (!(predicate)) {                                             \
                        fprintf(stderr, "Assertion failed '" #predicate "'\n"); \
                        exit(EXIT_FAILURE);                                     \
                }                                                               \
        } while (0)

void test_replace_chars(
        void
) {
        char str[DEFAULT_STRING_SIZE];

        strcpy(str, "String\" with\r chars\n");
        replace_chars(str, strlen(str));
        REQUIRE(!strcmp(str, "String' with  chars "));

        strcpy(str, "String without chars");
        replace_chars(str, strlen(str));
        REQUIRE(!strcmp(str, "String without chars"));
}

void test_skip_spaces(
        void
) {
        char str[DEFAULT_STRING_SIZE];
        char *res;

        strcpy(str, "   string with spaces in front");
        res = skip_spaces(str);
        REQUIRE(res == str + 3);

        strcpy(str, "string without spaces");
        res = skip_spaces(str);
        REQUIRE(res == str);
}

void test_truncate(
        void
) {
        char str[DEFAULT_STRING_SIZE];

        strcpy(str, "string with spaces in the end   ");
        truncate(str);
        REQUIRE(strlen(str) == 29);

        strcpy(str, "string without spaces in the end");
        truncate(str);
        REQUIRE(strlen(str) == 32);

        strcpy(str, "    ");
        truncate(str + 1); // skip first space
        REQUIRE(strlen(str + 1) == 0);
}

void test_move_memory_block(
        void
) {
        char str[DEFAULT_STRING_SIZE];
        char *to;
        char *from;
        char *res;

        strcpy(str, "string . with . markers");
        to = str;
        from = str + 7;
        res = move_memory_block(to, from, str + strlen(str));
        REQUIRE(!strcmp(str, ". with . markers"));
        REQUIRE(res == str + 16);
        REQUIRE(*res == '\0');

        strcpy(str, "string . with . markers");
        to = str + 7;
        from = str + 14;
        res = move_memory_block(to, from, str + strlen(str));
        REQUIRE(!strcmp(str, "string . markers"));
        REQUIRE(res == str + 16);
        REQUIRE(*res == '\0');

        strcpy(str, "string . with . markers");
        res = move_memory_block(str, str, str + strlen(str));
        REQUIRE(!strcmp(str, "string . with . markers"));
        REQUIRE(res == str + 23);
        REQUIRE(*res == '\0');
}

void test_extract_filename(
        void
) {
        char str[DEFAULT_STRING_SIZE];
        char *res;

        strcpy(str, "./file.txt");
        res = extract_filename(str);
        REQUIRE(!strcmp(res, "file"));

        strcpy(str, "C:\\dir\\file.txt");
        res = extract_filename(str);
        REQUIRE(!strcmp(res, "file"));
}

int main(
        void
) {
        test_replace_chars();
        test_skip_spaces();
        test_truncate();
        test_move_memory_block();
        test_extract_filename();
        return EXIT_SUCCESS;
}
