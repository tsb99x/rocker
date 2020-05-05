#pragma once

#include <node_pool.h>

#include <stdio.h>

void print(
        FILE *file,
        const char *base_name,
        node_pool_t *nodes
);
