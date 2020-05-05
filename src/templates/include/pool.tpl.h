#include <macro.h>

#ifndef PREFIX
#error "No PREFIX provided for pool template"
#endif

#ifndef T
#error "No T (base type) provided for pool template"
#endif

#define S EVAL(PREFIX, _pool)
#define O EVAL(S, _t)

typedef struct S O;

O *EVAL(init_, S)(
        size_t size
);

void EVAL(destroy_, S)(
        O *self
);

void EVAL(cleanup_, S)(
        O *self
);

#undef O
#undef S
#undef T
#undef PREFIX
