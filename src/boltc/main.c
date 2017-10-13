
#include <stdio.h>
#include <string.h>

#include "tokens.h"


int main(int argv, char **argc)
{
    tkn_t *t = tkn_new();

    tkn_push_vint(t, 10, 0, 0);
    tkn_push_vint(t, 18, 0, 0);
    const char *s = "something something bar";
    tkn_push_vstring(t, strlen(s), s);
    tkn_push_ident(t, "foo");
    const char *c = "# this is a comment";
    tkn_push_comment(t, c);

    token_t *tk;
    while (tk = tkn_next(t)) {
        switch (tk->header.type) {
        case TOKEN_COMMENT:
            printf("comment %s\n", tk->comment.body);
            break;
        case TOKEN_VINT:
            printf("int %d\n", tk->vint.value);
            break;
        case TOKEN_VSTRING:
            printf("str \"%*s\"\n", tk->vstring.length, tk->vstring.data);
            break;
        case TOKEN_IDENT:
            printf("ident %s\n", tk->ident.ident);
            break;
        default:
            printf("??? (%d)\n", tk->header.type);
        }
    }

    tkn_free(t);
    return 0;
}
