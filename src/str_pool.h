#pragma once

#include "status.h"

#define PREFIX str
#define T char
#include "templates/pool.tpl.h"

status_t copy_into_pool(
        str_pool_t *self,
        char **dest,
        const char *str,
        size_t len
);
