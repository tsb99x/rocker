#pragma once

#include "node.h"

#define PREFIX node
#define T struct node
#include "templates/pool.tpl.h"

struct node *emplace_node(
        struct node_pool *self,
        enum node_type type,
        const char *value
);

typedef void node_it(struct node *, void *);

void for_each_node(
        struct node_pool *self,
        void *state,
        node_it *handler
);
