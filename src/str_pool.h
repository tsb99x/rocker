#pragma once

#define PREFIX str
#define T char
#include "templates/pool.tpl.h"

char *copy_into_pool(
        struct str_pool *self,
        const char *str,
        size_t len
);
