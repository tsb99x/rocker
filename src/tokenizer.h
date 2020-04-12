#pragma once

#include <stdbool.h>

#include "str_pool.h"
#include "node_pool.h"

bool validate_braces(
        char *str,
        size_t len
);

void cleanup_literal(
        struct node *node,
        void *vstate
);

void tokenize(
        str_pool_t *strings,
        node_pool_t *nodes,
        char *buf,
        char *buf_end
);
