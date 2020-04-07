#include "string.h"

#include "string_utils.h"

void replace_chars(
        char *str_sz,
        size_t str_len
) {
        size_t rn_pos;
        while ((rn_pos = strcspn(str_sz, "\"\r\n")) != str_len) {
                str_sz[rn_pos] = (str_sz[rn_pos] == '"') ? '\'' : ' ';
        }
}

char *skip_spaces(
        char *str
) {
        while (*str == ' ' && *str != '\0')
                str++;
        return str;
}

char *move_memory_block(
        char *dst,
        char *beg,
        char *end
) {
        if (beg != dst) {
                ptrdiff_t diff = beg - dst;
                memmove(dst, beg, end - beg + 1); // include '\0'
                end -= diff;
        }
        return end;
}

void truncate(
        char *str_end
) {
        while (*(--str_end) == ' ');
        *(str_end + 1) = '\0';
}

void remove_file_ext(
        char *path
) {
        char *dot = strchr(path, '.');
        if (dot != NULL)
                *dot = '\0';
}

char *pick_filename(
        char *path
) {
        char *sep = strrchr(path, '/');
        if (sep == NULL)
                sep = strrchr(path, '\\');
        return (sep == NULL) ? path : sep + 1;
}
