#pragma once

#define PREFIX str
#define T char
#include "templates/pool.tpl.h"

char *copy_into_pool(
        str_pool_t *self,
        const char *str,
        size_t len
);
