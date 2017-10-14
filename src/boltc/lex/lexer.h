#pragma once

typedef struct lexer lexer_t;

lexer_t *lex_new();
void lex_free(lexer_t *lex);

int lex_step(lexer_t *lex);
token_t *lex_next(lexer_t *lex);
