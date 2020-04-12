#include "macro.h"

#include "node_pool.h"

#define PREFIX node
#define T struct node
#include "templates/pool.tpl.c"

struct node *emplace_node(
        node_pool_t *self,
        enum node_type type,
        char *value
) {
        struct node *ptr = self->last;
        ptr->type = type;
        ptr->value = value;
        if (++self->last >= self->limit)
                PANIC("Node pool is exhausted\n");
        return ptr;
}

void for_each_node(
        node_pool_t *self,
        void *state,
        node_it handler
) {
        for (struct node *it = self->ptr; it < self->last; it++)
                handler(it, state);
}
