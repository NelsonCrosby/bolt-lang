
#include <stdio.h>
#include <string.h>

#include "parser.h"


int main(int argv, char **argc)
{
    const char *lit =
        "#foo bar baz\n"
        " # box\n";

    mpc_parser_t *zp = zparser_new();

    mpc_result_t r;
    int status;

    if (status = mpc_parse("<literal>", lit, zp, &r)) {
        fprintf(stderr, "%s", r.output);
        free(r.output);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    mpc_cleanup(1, zp);

    return !status;
}
