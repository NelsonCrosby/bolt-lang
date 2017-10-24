
#include <stdio.h>
#include <string.h>

#include "parser.h"


int main(int argv, char **argc)
{
    const char *lit =
        "#foo bar baz\n"
        " # box\n"
        "\"fo\\oofoo\"# WHEEEE!\n";

    mpc_parser_t *zp = zparser_new();

    mpc_result_t r;
    int status;

    if (status = mpc_parse("<literal>", lit, zp, &r)) {
        zparser_ast_print(r.output, 0);
        zparser_ast_del(r.output);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    mpc_cleanup(1, zp);

    return !status;
}
