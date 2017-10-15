#pragma once

typedef struct lexer lexer_t;

lexer_t *lex_new_mem(size_t len, const char *src);
void lex_free(lexer_t *lex);

int lex_step(lexer_t *lex);
token_t *lex_next(lexer_t *lex);
