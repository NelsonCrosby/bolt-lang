
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "state.h"
#include "lexer.h"


struct lex_store_mem {
    const char *src;
    size_t len, pos;
};
static int lex_step_mem(lexer_t *lex);

union lex_store {
    struct lex_store_mem mem;
};

struct lexer {
    token_list_t *tokens;
    int (*step)(lexer_t *lex);
    union lex_store store;
    zlex_state_t *sm_state;
};


static lexer_t *lex_new(size_t src_len, const char *src)
{
    lexer_t *lex = malloc(sizeof (*lex));
    lex->tokens = tkl_new();
    lex->sm_state = zlex_state_new(lex->tokens, src_len, src);
    return lex;
}

lexer_t *lex_new_mem(size_t len, const char *src)
{
    lexer_t *lex = lex_new(len, src);
    lex->step = lex_step_mem;
    lex->store.mem.src = src;
    lex->store.mem.len = len;
    lex->store.mem.pos = 0;

    return lex;
}


void lex_free(lexer_t *lex)
{
    tkl_free(lex->tokens);
    free(lex);
}


int lex_step(lexer_t *lex)
{
    return lex->step(lex);
}

static int lex_step_mem(lexer_t *lex)
{
    switch (zlex_state_step(lex->sm_state)) {
    case ZLEX_STATE_PROCESSING:
    case ZLEX_STATE_NEWTOKEN:
        return 0;
    case ZLEX_STATE_NONELEFT:
        return 1;
    case ZLEX_STATE_INVALID:
        return -1;
    }
}


token_t *lex_next(lexer_t *lex)
{
    return tkl_next(lex->tokens);
}
