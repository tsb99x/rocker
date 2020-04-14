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

status_t tokenize(
        str_pool_t *strings,
        node_pool_t *nodes,
        char *buf,
        char *buf_end
) {
        status_t err = NO_ERROR;
        char *sz_loc;
        char *op_brace;
        char *ed_brace;

        while ((op_brace = strstr(buf, "{{")) != NULL) {
                err = copy_into_pool(strings, &sz_loc, buf, op_brace - buf);
                if (err) return err;

                err = emplace_node(nodes, LITERAL, sz_loc);
                if (err) return err;

                op_brace += 2; // skip "{{"
                ed_brace = strstr(buf, "}}");

                err = copy_into_pool(strings, &sz_loc, op_brace, ed_brace - op_brace);
                if (err) return err;

                err = emplace_node(nodes, VARIABLE, sz_loc);
                if (err) return err;

                buf = ed_brace + 2; // skip "}}"
        }

        if (buf < buf_end) {
                err = copy_into_pool(strings, &sz_loc, buf, buf_end - buf);
                if (err) return err;

                err = emplace_node(nodes, LITERAL, sz_loc);
                if (err) return err;
        }

        return NO_ERROR;
}
