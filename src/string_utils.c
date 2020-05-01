#include <string.h>

#include "string_utils.h"

void replace_chars(
        char *str,
        size_t len
) {
        size_t rn_pos;

        while ((rn_pos = strcspn(str, "\"\r\n")) != len)
                str[rn_pos] = (str[rn_pos] == '"') ? '\'' : ' ';
}

char *skip_spaces(
        char *str
) {
        while (*str == ' ')
                str++;
        return str;
}

void truncate(
        char *str
) {
        char *str_end;

        str_end = str + strlen(str) - 1; // at last char
        while (*str_end == ' ' && str_end >= str)
                str_end--;
        *(str_end + 1) = '\0'; // go back and replace last space
}

char *move_memory_block(
        char *dst,
        char *beg,
        char *end
) {
        ptrdiff_t diff;

        if (beg == dst)
                return end;
        diff = beg - dst;
        memmove(dst, beg, end - beg + 1); // include '\0'
        return end - diff;
}

char *extract_filename(
        char *path
) {
        char *sep, *dot;

        sep = strrchr(path, '/');
        if (sep == NULL)
                sep = strrchr(path, '\\');
        path = (sep == NULL) ? path : sep + 1; // skip separator char
        dot = strchr(path, '.');
        if (dot != NULL)
                *dot = '\0';
        return path;
}
