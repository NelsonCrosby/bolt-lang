#pragma once

#include <mpc/mpc.h>

typedef struct zparser_ast {
    enum _zparser_ast_type {
        ZPARSER_AST_COMMENT,
        ZPARSER_AST_STRING,

        ZPARSER_AST_NODELIST
    } type;
    union _zparser_ast_data {
        const char *comment;
        const char *string;

        struct zparser_ast_nodelist {
            size_t size, length;
            struct zparser_ast **nodes;
        } nodelist;
    } data;
} zparser_ast_t;

mpc_parser_t *zparser_new();

void zparser_ast_print(zparser_ast_t *ast, int indent);
void zparser_ast_del(zparser_ast_t *ast);
