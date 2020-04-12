#include <string.h>
#include <stddef.h>

#include "macro.h"
#include "str_pool.h"
#include "node_pool.h"
#include "string_utils.h"
#include "printer.h"

#define STR_POOL_SIZE 65535
#define NODES_POOL_SIZE 256
#define DEF_STR_SIZE 128

long file_size(
        FILE *file
) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        return size;
}

void cleanup_literal(
        char *lit
) {
        char *lit_end = lit + strlen(lit);

        char *first_char = skip_spaces(lit);
        lit_end = move_memory_block(lit, first_char, lit_end);

        char *ed_brace = lit;
        while ((ed_brace = strchr(ed_brace, '>')) != NULL) {
                ed_brace++; // skip '>'
                char *ch = skip_spaces(ed_brace);
                if (*ch != '<')
                        continue;
                lit_end = move_memory_block(ed_brace, ch, lit_end);
        }

        truncate(lit);
}

void split_tokens(
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
                cleanup_literal(sz_loc);
                emplace_node(nodes, LITERAL, sz_loc);

                op_brace += 2; // skip "{{"
                ed_brace = strstr(buf, "}}");
                if (ed_brace == NULL) {
                        puts("Closing }} braces not found!");
                        return; // FIXME : think about this case!
                }

                sz_loc = copy_into_pool(strings, op_brace, ed_brace - op_brace);
                cleanup_literal(sz_loc);
                emplace_node(nodes, VARIABLE, sz_loc);
                
                buf = ed_brace + 2; // skip "}}"
        }

        if (buf <= buf_end) {
                sz_loc = copy_into_pool(strings, buf, buf_end - buf);
                cleanup_literal(sz_loc);
                emplace_node(nodes, LITERAL, sz_loc);
        }
}

#define SRC_BUF_SIZE 65535
char src_buf[SRC_BUF_SIZE];

size_t load_file_to_buf(
        const char *filename,
        char *buf,
        size_t buf_size
) {
        FILE *file = fopen(filename, "rb");
        if (file == NULL)
                PANIC("Error opening file %s\n", filename);

        long size = file_size(file);
        if (size >= (long) buf_size) {
                fclose(file);
                PANIC("No enough memory to load source file\n");
        }

        fread(buf, sizeof(char), size, file);
        src_buf[size] = '\0';

        fclose(file);
        return size;
}

int main(
        int argc,
        char **argv
) {
        if (argc < 2)
                PANIC("At least one template base name is required!\n");

        str_pool_t *strings = init_str_pool(STR_POOL_SIZE);
        node_pool_t *nodes = init_node_pool(NODES_POOL_SIZE);

        for (int i = 1; i < argc; i++) { // skip program name
                char *base_name = extract_filename(argv[i]);

                char input[DEF_STR_SIZE];
                snprintf(input, DEF_STR_SIZE, "%s.hbs", argv[i]);

                char output[DEF_STR_SIZE];
                snprintf(output, DEF_STR_SIZE, "%s.h", argv[i]);

                printf("Generating '%s' from '%s' ... ", output, input);
                fflush(stdout);

                size_t input_size = load_file_to_buf(input, src_buf, SRC_BUF_SIZE);
                replace_chars(src_buf, input_size);
                split_tokens(strings, nodes, src_buf, src_buf + input_size);

                FILE *file = fopen(output, "w");
                if (file == NULL)
                        PANIC("Error opening file %s\n", output);

                print(file, base_name, nodes);
                fclose(file);

                cleanup_str_pool(strings);
                cleanup_node_pool(nodes);

                printf("Success!\n");
        }

        destroy_node_pool(nodes);
        destroy_str_pool(strings);
        return EXIT_SUCCESS;
}
