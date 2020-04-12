#include <string.h>
#include <stddef.h>

#include "macro.h"
#include "str_pool.h"
#include "node_pool.h"
#include "string_utils.h"
#include "tokenizer.h"
#include "printer.h"

#define STR_POOL_SIZE 65535
#define NODES_POOL_SIZE 256
#define DEF_STR_SIZE 128

long file_size(
        FILE *file
) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);
        return size;
}

#define SRC_BUF_SIZE 65535
char src_buf[SRC_BUF_SIZE];

size_t load_file_to_buf(
        FILE *input,
        char *buf,
        size_t buf_size
) {
        long size = file_size(input);
        if (size >= (long) buf_size) {
                fclose(input);
                PANIC("No enough memory to load source file\n");
        }
        fread(buf, sizeof(char), size, input);
        src_buf[size] = '\0';
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

                FILE *file_in = fopen(input, "rb");
                if (file_in == NULL)
                        PANIC("Error opening file %s\n", input);
                size_t input_size = load_file_to_buf(file_in, src_buf, SRC_BUF_SIZE);
                fclose(file_in);

                if (!validate_braces(src_buf, input_size))
                        PANIC("Unbalanced braces found\n");

                replace_chars(src_buf, input_size);
                tokenize(strings, nodes, src_buf, src_buf + input_size);

                for_each_node(nodes, NULL, cleanup_literal);

                FILE *file_out = fopen(output, "w");
                if (file_out == NULL)
                        PANIC("Error opening file %s\n", output);
                print(file_out, base_name, nodes);
                fclose(file_out);

                cleanup_str_pool(strings);
                cleanup_node_pool(nodes);

                printf("Success!\n");
        }

        destroy_node_pool(nodes);
        destroy_str_pool(strings);
        return EXIT_SUCCESS;
}
