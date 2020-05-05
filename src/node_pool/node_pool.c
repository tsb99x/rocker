#include <node_pool.h>

#include <macro.h>

#define PREFIX node
#define T struct node
#include <pool.tpl.c>

status_t emplace_node(
        node_pool_t *self,
        enum node_type type,
        char *value
) {
        struct node *ptr;

        ptr = self->last;
        ptr->type = type;
        ptr->value = value;
        if (++self->last >= self->limit)
                return NODE_POOL_OVERFLOW;
        return NO_ERROR;
}

void for_each_node(
        node_pool_t *self,
        void *state,
        node_it handler
) {
        struct node *it;

        for (it = self->ptr; it < self->last; it++)
                handler(it, state);
}
