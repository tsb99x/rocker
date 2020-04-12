#include <string.h>

#include "macro.h"
#include "string_utils.h"

#include "tokenizer.h"

bool validate_braces(
        char *str,
        size_t len
) {
        int braces_count = 0;
        for (size_t i = 0; i < len; i++) {
                if (str[i] == '{')
                        if (++braces_count > 2)
                                return false;
                if (str[i] == '}')
                        if (--braces_count < 0)
                                return false;
        }
        return 0 == braces_count;
}

void cleanup_literal(
        struct node *node,
        void *vstate
) {
        UNUSED(vstate);

        char *it = node->value;
        char *it_end = it + strlen(it);

        char *first_char = skip_spaces(it);
        it_end = move_memory_block(it, first_char, it_end);

        char *ed_brace = it;
        while ((ed_brace = strchr(ed_brace, '>')) != NULL) {
                ed_brace++; // skip '>'
                char *ch = skip_spaces(ed_brace);
                if (*ch != '<')
                        continue;
                it_end = move_memory_block(ed_brace, ch, it_end);
        }

        truncate(it);
}

void tokenize(
        str_pool_t *strings,
        node_pool_t *nodes,
        char *buf,
        char *buf_end
) {
        char *sz_loc;
        char *op_brace;
        char *ed_brace;

        while ((op_brace = strstr(buf, "{{")) != NULL) {
                sz_loc = copy_into_pool(strings, buf, op_brace - buf);
                emplace_node(nodes, LITERAL, sz_loc);
                op_brace += 2; // skip "{{"
                ed_brace = strstr(buf, "}}");
                sz_loc = copy_into_pool(strings, op_brace, ed_brace - op_brace);
                emplace_node(nodes, VARIABLE, sz_loc);
                buf = ed_brace + 2; // skip "}}"
        }

        if (buf < buf_end) {
                sz_loc = copy_into_pool(strings, buf, buf_end - buf);
                emplace_node(nodes, LITERAL, sz_loc);
        }
}
