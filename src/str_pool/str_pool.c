#include <str_pool.h>

#include <status.h>
#include <macro.h>

#include <string.h>

#define PREFIX str
#define T char
#include <pool.tpl.c>

status_t copy_into_pool(
        str_pool_t *self,
        char **dest,
        const char *str,
        size_t len
) {
        *dest = self->last;
        if (*dest + len >= self->limit)
                return STR_POOL_OVERFLOW;
        memcpy(*dest, str, len);
        self->last += len;
        *self->last = '\0';
        self->last++;
        return NO_ERROR;
}
