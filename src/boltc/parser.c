
#include <sys/types.h>
#include <stdlib.h>

#include "parser.h"

static mpc_val_t *zparse_ast_comment_new(mpc_val_t *comment)
{
    zparser_ast_t *ast = malloc(sizeof(*ast));
    ast->type = ZPARSER_AST_COMMENT;
    ast->data.comment = comment;
    return ast;
}

static void zparse_ast_comment_del(mpc_val_t *comment)
{
    zparser_ast_t *ast = (zparser_ast_t *) comment;
    char *data = (char *) ast->data.comment;
    ast->data.comment = NULL;
    free(data);
    free(comment);
}

static void zparse_ast_comment_print(zparser_ast_t *ast)
{
    printf("<comment> =\n%s", ast->data.comment);
}

static mpc_parser_t *zparser_comment()
{
    mpc_parser_t *parser = mpc_new("comment");
    // { # ([^\n] * \n) } +
    mpc_define(
        parser,
        mpc_apply(
            mpc_many1(          // (... +)
                mpcf_strfold,
                mpc_and(            // # (...)
                    2, mpcf_snd,
                    mpc_stripl(mpc_apply(mpc_char('#'), mpcf_free)),
                    mpc_and(        // (... \n)
                        2, mpcf_strfold,
                        mpc_many(   // ([^\n] *)
                            mpcf_strfold,
                            mpc_and(
                                2, mpcf_snd,
                                mpc_not(mpc_newline(), free),
                                mpc_any(),
                                mpcf_dtor_null
                            )
                        ),
                        mpc_newline(),  // (\n)
                        free
                    ),
                    free
                )
            ),
            zparse_ast_comment_new
        )
    );
    return parser;
}


static mpc_val_t *zparse_ast_string_new(mpc_val_t *data)
{
    zparser_ast_t *ast = malloc(sizeof(*ast));
    ast->type = ZPARSER_AST_STRING;
    ast->data.string = data;
    return ast;
}

static void (*zparse_ast_string_del)(mpc_val_t *ast) =
    zparse_ast_comment_del;

static void zparse_ast_string_print(zparser_ast_t *ast)
{
    printf("<string> = \"%s\"\n", ast->data.string);
}

static mpc_parser_t *zparser_string()
{
    mpc_parser_t *parser = mpc_new("string");
    mpc_define(
        parser,
        mpc_apply(
            mpc_strip(mpc_string_lit()),
            zparse_ast_string_new
        )
    );
    return parser;
}


static zparser_ast_t *zparse_ast_nodelist_new(size_t size)
{
    zparser_ast_t *ast = malloc(sizeof(*ast));
    ast->type = ZPARSER_AST_NODELIST;
    struct zparser_ast_nodelist *nl = &ast->data.nodelist;
    nl->size = size;
    nl->length = 0;
    if (size) {
        nl->nodes = calloc(size, sizeof(*nl->nodes));
        memset(nl->nodes, 0, size * sizeof(*nl->nodes));
    } else {
        nl->nodes = NULL;
    }
    return ast;
}

static void zparse_ast_nodelist_del(zparser_ast_t *ast)
{
    struct zparser_ast_nodelist *nl = &ast->data.nodelist;
    off_t i = nl->length;
    while (i-- > 0) {
        free(nl->nodes[i]);
    }
    free(ast);
}

static void zparse_ast_nodelist_print(zparser_ast_t *ast, int nidt)
{
    printf("<nodelist> =\n");
    struct zparser_ast_nodelist *nl = &ast->data.nodelist;
    for (off_t i = 0; i < nl->length; i++) {
        zparser_ast_print(nl->nodes[i], nidt);
    }
}

static int zparse_ast_nodelist_add(zparser_ast_t *ast, zparser_ast_t *new)
{
    struct zparser_ast_nodelist *nl = &ast->data.nodelist;

    if (nl->length == nl->size){
        nl->size *= 2;
        nl->nodes = realloc(nl->nodes, nl->size * sizeof(*nl->nodes));
        memset(nl->nodes + nl->length, 0, nl->length * sizeof(*nl->nodes));
    }

    nl->nodes[nl->length++] = new;
    return 0;
}

static mpc_val_t *zparse_ast_nodelist_fold(int n, mpc_val_t **in)
{
    zparser_ast_t *ast = zparse_ast_nodelist_new(n);
    for (int i = 0; i < n; i++) {
        zparse_ast_nodelist_add(ast, (zparser_ast_t *) in[i]);
    }
    return ast;
}

static mpc_parser_t *zparser_nodelist()
{
    mpc_parser_t *parser = mpc_new("nodelist");
    mpc_define(
        parser,
        mpc_many(
            zparse_ast_nodelist_fold,
            mpc_or(
                2,
                zparser_comment(),
                zparser_string()
            )
        )
    );
    return parser;
}


mpc_parser_t *zparser_new()
{
    return mpc_whole(
        zparser_nodelist(),
        free
    );
}


void zparser_ast_print(zparser_ast_t *ast, int indent)
{
    if (!ast) return;

    int i = indent;
    while (i-- > 0) {
        printf("  ");
    }

    switch (ast->type) {
    case ZPARSER_AST_COMMENT:
        zparse_ast_comment_print(ast);
        break;
    case ZPARSER_AST_STRING:
        zparse_ast_string_print(ast);
        break;
    case ZPARSER_AST_NODELIST:
        zparse_ast_nodelist_print(ast, indent + 1);
        break;
    }
}

void zparser_ast_del(zparser_ast_t *ast)
{
    switch (ast->type) {
    case ZPARSER_AST_COMMENT:
        zparse_ast_comment_del(ast);
        break;
    case ZPARSER_AST_STRING:
        zparse_ast_string_del(ast);
        break;
    case ZPARSER_AST_NODELIST:
        zparse_ast_nodelist_del(ast);
        break;
    }
}
