#ifndef __NODE_H__
#define __NODE_H__

enum node_type {
        LITERAL,
        VARIABLE
};

struct node {
        enum node_type type;
        const char *value;
};

#endif
