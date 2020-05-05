#include <printer.h>

#include <node_pool.h>

#include <stddef.h>
#include <string.h>

#define TAB "        "

struct count_state {
        size_t vars_count;
};

void count_variables(
        struct node *el,
        void *state
) {
        struct count_state *c_state = (struct count_state *) state;
        if (VARIABLE == el->type)
                c_state->vars_count++;
}

struct output_state {
        FILE *file;
};

void output_var_into_param(
        struct node *el,
        void *state
) {
        struct output_state *o_state = (struct output_state *) state;
        if (el->type != VARIABLE)
                return;
        fprintf(o_state->file,
                TAB "const char *%s;\n",
                el->value);
}

void output_copy_process(
        struct node *el,
        void *state
) {
        struct output_state *o_state = (struct output_state *) state;
        if (el->type == LITERAL) {
                size_t len = strlen(el->value);
                fprintf(o_state->file,
                        TAB "memcpy(it, \"%s\", %zu);\n" \
                        TAB "it += %zu;\n",
                        el->value, len, len);
        }
        if (el->type == VARIABLE) {
                fprintf(o_state->file,
                        TAB "if (params->%s != NULL) {\n" \
                        TAB TAB "size_t len = strlen(params->%s);\n" \
                        TAB TAB "strcpy(it, params->%s);\n" \
                        TAB TAB "it += len;\n" \
                        TAB "}\n",
                        el->value, el->value, el->value);
        }
}

void print(
        FILE *file,
        const char *base_name,
        node_pool_t *nodes
) {
        size_t vars_count;
        struct count_state c_state = {.vars_count = 0};
        struct output_state o_state = {.file = file};

        fprintf(file,
                "#pragma once\n" \
                "\n" \
                "#include <string.h>\n" \
                "\n");

        for_each_node(nodes, &c_state, count_variables);
        vars_count = c_state.vars_count;

        if (vars_count > 0) {
                fprintf(file,
                        "struct %s_params {\n",
                        base_name);
                for_each_node(nodes, &o_state, output_var_into_param);
                fprintf(file,
                        "};\n" \
                        "\n");
        }

        fprintf(file,
                "size_t %s_template(\n",
                base_name);

        if (vars_count > 0)
                fprintf(file,
                        TAB "const struct %s_params *params,\n",
                        base_name);

        fprintf(file,
                TAB "char *dst\n" \
                ") {\n" \
                TAB "char *it = dst;\n");
        for_each_node(nodes, &o_state, output_copy_process);
        fprintf(file,
                TAB "return it - dst;\n" \
                "}\n");
}
