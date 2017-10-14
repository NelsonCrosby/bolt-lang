
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "lexer.h"


struct lexer {
    token_list_t *tokens;
    _Bool done;
};


lexer_t *lex_new()
{
    lexer_t *lex = malloc(sizeof (lex));
    lex->tokens = tkl_new();
    lex->done = 0;

    return lex;
}


void lex_free(lexer_t *lex)
{
    tkl_free(lex->tokens);
    free(lex);
}


int lex_step(lexer_t *lex)
{
    // TODO: Real stepping over file
    if (lex->done) {
        return 1;
    } else {
        tkl_push_comment(lex->tokens, "# These are some example tokens.");
        tkl_push_ident(lex->tokens, "main");
        tkl_push(lex->tokens, TOKEN_PAREN_OPEN);
        tkl_push_ident(lex->tokens, "args");
        tkl_push(lex->tokens, TOKEN_OP_DECL);
        tkl_push_ident(lex->tokens, "Array");
        tkl_push(lex->tokens, TOKEN_RPAREN_OPEN);
        tkl_push_ident(lex->tokens, "String");
        tkl_push(lex->tokens, TOKEN_RPAREN_CLOSE);
        tkl_push(lex->tokens, TOKEN_PAREN_CLOSE);
        tkl_push(lex->tokens, TOKEN_OP_DECL);
        tkl_push_ident(lex->tokens, "int");
        tkl_push(lex->tokens, TOKEN_KW_DO);
        tkl_push_ident(lex->tokens, "io");
        tkl_push(lex->tokens, TOKEN_OP_ACCESS);
        tkl_push_ident(lex->tokens, "print");
        tkl_push(lex->tokens, TOKEN_PAREN_OPEN);
        const char *hw = "Hello, World!";
        tkl_push_vstring(lex->tokens, strlen(hw), hw);
        tkl_push(lex->tokens, TOKEN_PAREN_CLOSE);
        tkl_push(lex->tokens, TOKEN_KW_END);
        
        lex->done = 1;
        return 0;
    }
}


token_t *lex_next(lexer_t *lex)
{
    return tkl_next(lex->tokens);
}
