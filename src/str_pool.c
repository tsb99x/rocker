#include <string.h>

#include "macro.h"

#include "str_pool.h"

#define PREFIX str
#define T char
#include "templates/pool.tpl.c"

char *copy_into_pool(
        struct str_pool *self,
        const char *str,
        size_t len
) {
        char *ptr = self->last;
        if (ptr + len >= self->limit)
                PANIC("String pool is exhausted\n");
        memcpy(ptr, str, len);
        self->last += len;
        *self->last = '\0';
        self->last++;
        return ptr;
}
