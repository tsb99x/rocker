#include <macro.h>

#ifndef PREFIX
#error "No PREFIX provided for pool template"
#endif

#ifndef T
#error "No T (base type) provided for pool template"
#endif

#define S EVAL(PREFIX, _pool)
#define O EVAL(S, _t)

struct S {
        T *ptr;
        T *last;
        T *limit;
};

O *EVAL(init_,S)(
        size_t size
) {
        T *mem;
        struct S *pool;

        mem = malloc(size * sizeof(T));
        if (mem == NULL)
                PANIC("Failed to allocate memory for pool data\n");
        pool = malloc(sizeof(struct S));
        if (pool == NULL)
                PANIC("Failed to allocate memory for pool struct\n");
        pool->ptr = mem;
        pool->last = mem;
        pool->limit = mem + size;
        return pool;
}

void EVAL(destroy_,S)(
        O *self
) {
        free(self->ptr);
        free(self);
}

void EVAL(cleanup_,S)(
        O *self
) {
        self->last = self->ptr;
}

#undef O
#undef S
#undef T
#undef PREFIX
