
#include <stdio.h>
#include <string.h>

#include "lex/tokens.h"
#include "lex/lexer.h"


int main(int argv, char **argc)
{
    const char *src = " \n"
        "# This is a comment.\n"
        "# And another... \n";
    lexer_t *lex = lex_new_mem(strlen(src), src);
    while (!lex_step(lex)) {}

    for (token_t *t; t = lex_next(lex); ) {
        switch (t->header.type) {
        case TOKEN_COMMENT:
            printf("#%s\n", t->comment.body);
            break;
        case TOKEN_VINT:
            switch (t->vint.repr) {
            case TOKEN_VINT_BIN:
            case TOKEN_VINT_HEX:
                printf("0x%llX", t->vint.value);
                break;
            default:
                printf("%lld", t->vint.value);
                break;
            }
            break;
        case TOKEN_VSTRING:
            printf("\"%*s\"", t->vstring.length, t->vstring.data);
            break;
        case TOKEN_IDENT:
            printf("%s", t->ident.ident);
            break;
        case TOKEN_KW_DO:
            printf(" do\n");
            break;
        case TOKEN_KW_END:
            printf("\nend\n");
            break;
        case TOKEN_OP_DECL:
            printf(": ");
            break;
        case TOKEN_OP_ACCESS:
            printf(".");
            break;
        case TOKEN_OP_COMMA:
            printf(", ");
            break;
        case TOKEN_PAREN_OPEN:
            printf("(");
            break;
        case TOKEN_PAREN_CLOSE:
            printf(")");
            break;
        case TOKEN_RPAREN_OPEN:
            printf("[");
            break;
        case TOKEN_RPAREN_CLOSE:
            printf("]");
            break;
        default:
            printf(" {? %d ?}", t->header.type);
        }
    }

    lex_free(lex);
    return 0;
}
