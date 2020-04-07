#include <stdio.h>
#include <stdlib.h>

#include "node_pool.h"

#define PREFIX node
#define T struct node
#include "templates/pool.tpl.c"

struct node *emplace_node(
        struct node_pool *self,
        enum node_type type,
        const char *value
) {
        struct node *ptr = self->last;
        ptr -> type = type;
        ptr -> value = value;
        if (++self->last >= self->limit) {
                fprintf(stderr, "Buffer is exhausted\n");
                exit(EXIT_FAILURE);
        }
        return ptr;
}

void for_each_node(
        struct node_pool *self,
        void *state,
        node_it handler
) {
        for (struct node *it = self->ptr; it < self->last; it++)
                handler(it, state);
}
