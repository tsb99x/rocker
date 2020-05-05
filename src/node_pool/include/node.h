#pragma once

enum node_type {
        LITERAL,
        VARIABLE
};

struct node {
        enum node_type type;
        char *value;
};
