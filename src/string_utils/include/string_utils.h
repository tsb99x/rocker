#pragma once

#include <stddef.h>

void replace_chars(
        char *str,
        size_t len
);

char *skip_spaces(
        char *str
);

void truncate(
        char *str
);

char *move_memory_block(
        char *dst,
        char *beg,
        char *end
);

char *extract_filename(
        char *path
);
