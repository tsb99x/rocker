#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>

void print(
        FILE *file,
        const char *base_name,
        struct node_pool *nodes
);

#endif
