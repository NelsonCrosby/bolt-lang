
#include <stdio.h>
#include <string.h>

#include "tokens.h"


int main(int argv, char **argc)
{
    tkn_t *t = tkn_new();

    token_t token;
    token.header.type = TOKEN_INTEGER;
    token.integer.value = 10;
    tkn_push(t, token);

    token.integer.value = 18;
    tkn_push(t, token);

    token.header.type = TOKEN_IDENT;
    token.ident.ident = "foo";
    tkn_push(t, token);

    token.header.type = TOKEN_STRING;
    token.string.data = "something something bar";
    token.string.length = strlen(token.string.data);
    tkn_push(t, token);

    token_t *tk;
    while (tk = tkn_next(t)) {
        switch (tk->header.type) {
        case TOKEN_IDENT:
            printf("ident %s\n", tk->ident.ident);
            break;
        case TOKEN_INTEGER:
            printf("int %d\n", tk->integer.value);
            break;
        case TOKEN_STRING:
            printf("str \"%*s\"\n", tk->string.length, tk->string.data);
            break;
        default:
            printf("??? (%d)\n", tk->header.type);
        }
    }

    tkn_free(t);
    return 0;
}
