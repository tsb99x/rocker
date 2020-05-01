#include <stdbool.h>

#include "macro.h"
#include "node_pool.h"

#include "printer.h"

#define NODE_POOL_SIZE 32

bool contents_are_same(
        FILE *a,
        FILE *b
) {
        char cha, chb;
        size_t line;

        line = 1;
        while ((cha = fgetc(a)) != EOF) {
                chb = fgetc(b);
                if (chb == EOF) {
                        fprintf(stderr,
                                "Files have different lengths\n");
                        return false;
                }
                if (cha == '\n')
                        line++;
                if (cha != chb) {
                        fprintf(stderr,
                                "Different chars (line %zu): '%c' is not '%c'\n",
                                line, cha, chb);
                        return false;
                }
        }
        if ((chb = fgetc(b)) != EOF) {
                fprintf(stderr,
                        "File b is not finished, contents:\n'");
                while ((chb = fgetc(b)) != EOF)
                        fputc(chb, stderr);
                fputs("'\n", stderr);
                return false;
        }
        return true;
}

FILE *create_tmp_file(
        void
) {
        FILE *file;

        file = tmpfile();
        if (file == NULL)
                PANIC("Failed to create tmp file\n");
        return file;
}

void test_print(
        void
) {
        FILE *sink, *expect;
        node_pool_t *nodes;

        sink = create_tmp_file();
        expect = create_tmp_file();
        nodes = init_node_pool(NODE_POOL_SIZE);

        emplace_node(nodes, LITERAL, "simple text '");
        emplace_node(nodes, VARIABLE, "variable");
        emplace_node(nodes, LITERAL, "' text again");

        print(sink, "tmp", nodes);
        rewind(sink);
        fprintf(expect,
                "#pragma once\n"                                               \
                "\n"                                                           \
                "#include <string.h>\n"                                        \
                "\n"                                                           \
                "struct tmp_params {\n"                                        \
                "        const char *variable;\n"                              \
                "};\n"                                                         \
                "\n"                                                           \
                "size_t tmp_template(\n"                                       \
                "        const struct tmp_params *params,\n"                   \
                "        char *dst\n"                                          \
                ") {\n"                                                        \
                "        char *it = dst;\n"                                    \
                "        memcpy(it, \"simple text '\", 13);\n"                 \
                "        it += 13;\n"                                          \
                "        if (params->variable != NULL) {\n"                    \
                "                size_t len = strlen(params->variable);\n"     \
                "                strcpy(it, params->variable);\n"              \
                "                it += len;\n"                                 \
                "        }\n"                                                  \
                "        memcpy(it, \"' text again\", 12);\n"                  \
                "        it += 12;\n"                                          \
                "        return it - dst;\n"                                   \
                "}\n");
        rewind(expect);
        REQUIRE(contents_are_same(expect, sink));

        rewind(sink);
        rewind(expect);
        cleanup_node_pool(nodes);

        emplace_node(nodes, LITERAL, "simple text and only text");

        print(sink, "tmp", nodes);
        rewind(sink);
        fprintf(expect,
                "#pragma once\n"                                               \
                "\n"                                                           \
                "#include <string.h>\n"                                        \
                "\n"                                                           \
                "size_t tmp_template(\n"                                       \
                "        char *dst\n"                                          \
                ") {\n"                                                        \
                "        char *it = dst;\n"                                    \
                "        memcpy(it, \"simple text and only text\", 25);\n"     \
                "        it += 25;\n"                                          \
                "        return it - dst;\n"                                   \
                "}\n");
        rewind(expect);
        REQUIRE(contents_are_same(expect, sink));

        destroy_node_pool(nodes);
        fclose(expect);
        fclose(sink);
}

int main(
        void
) {
        test_print();
        return EXIT_SUCCESS;
}
