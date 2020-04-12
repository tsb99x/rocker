#pragma once

#include "node.h"

#define PREFIX node
#define T struct node
#include "templates/pool.tpl.h"

struct node *emplace_node(
        node_pool_t *self,
        enum node_type type,
        char *value
);

typedef void node_it(struct node *, void *);

void for_each_node(
        node_pool_t *self,
        void *state,
        node_it *handler
);
