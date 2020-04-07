#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <stddef.h>

void replace_chars(
        char *str_sz,
        size_t str_len
);

char *skip_spaces(
        char *str
);

char *move_memory_block(
        char *dst,
        char *beg,
        char *end
);

void truncate(
        char *str_end
);

void remove_file_ext(
        char *path
);

char *pick_filename(
        char *path
);

#endif
