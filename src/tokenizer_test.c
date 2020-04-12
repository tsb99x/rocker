#include <stdlib.h>
#include <string.h>

#include "macro.h"

#include "tokenizer.h"

#define DEF_SIZE 1024

void test_validate_braces(
        void
) {
        char *str;
        bool res;
        
        str = "valid {{ val }} string";
        res = validate_braces(str, strlen(str));
        REQUIRE(res == true);

        str = "erroneous {{ val {{ err }} }} string";
        res = validate_braces(str, strlen(str));
        REQUIRE(res == false);

        str = "another }} err {{ string";
        res = validate_braces(str, strlen(str));
        REQUIRE(res == false);
}

struct cmp_state {
        size_t pos;
        size_t size;
        struct node *expected;
};

void compare(
        struct node *it,
        void *vstate
) {
        struct cmp_state *state = (struct cmp_state *) vstate;
        REQUIRE(it->type == state->expected[state->pos].type);
        REQUIRE(!strcmp(it->value, state->expected[state->pos].value));
        REQUIRE(++state->pos <= state->size);
}

#ifdef WIN32
#define STRDUP _strdup
#else
#define STRDUP strdup
#endif

void test_cleanup_literal(
        void
) {
        char *var;
        struct node temp;

        var = STRDUP("   var   ");
        temp = (struct node) {.type = VARIABLE, .value = var};
        cleanup_literal(&temp, NULL);
        REQUIRE(temp.type == VARIABLE);
        REQUIRE(!strcmp(temp.value, "var"));
        free(var);

        var = STRDUP("   <html> <head>     </head> </html>   ");
        temp = (struct node) {.type = LITERAL, .value = var};
        cleanup_literal(&temp, NULL);
        REQUIRE(temp.type == LITERAL);
        REQUIRE(!strcmp(temp.value, "<html><head></head></html>"));
        free(var);
}

void test_tokenize(
        void
) {
        str_pool_t *strings = init_str_pool(DEF_SIZE);
        node_pool_t *nodes = init_node_pool(DEF_SIZE);
        char *input;

        input = "simple string";
        tokenize(strings, nodes, input, input + strlen(input));
        for_each_node(nodes, &(struct cmp_state) {
                .pos = 0,
                .size = 1,
                .expected = (struct node[]) {
                        {.type = LITERAL, .value = "simple string"}
                }
        }, compare);

        cleanup_str_pool(strings);
        cleanup_node_pool(nodes);

        input = "simple {{ test }}";
        tokenize(strings, nodes, input, input + strlen(input));
        for_each_node(nodes, &(struct cmp_state) {
                .pos = 0,
                .size = 2,
                .expected = (struct node[]) {
                        {.type = LITERAL, .value = "simple "},
                        {.type = VARIABLE, .value = " test "}
                }
        }, compare);

        cleanup_str_pool(strings);
        cleanup_node_pool(nodes);

        input = "simple {{ test }} string";
        tokenize(strings, nodes, input, input + strlen(input));
        for_each_node(nodes, &(struct cmp_state) {
                .pos = 0,
                .size = 3,
                .expected = (struct node[]) {
                        {.type = LITERAL, .value = "simple "},
                        {.type = VARIABLE, .value = " test "},
                        {.type = LITERAL, .value = " string"}
                }
        }, compare);
}

int main(
        void
) {
        test_validate_braces();
        test_cleanup_literal();
        test_tokenize();
        return EXIT_SUCCESS;
}
