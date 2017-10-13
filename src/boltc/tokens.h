#pragma once

#include <stdlib.h>

typedef enum token_type {
    TOKEN_IDENT,
    TOKEN_INTEGER,
    TOKEN_STRING
} token_type_t;

typedef struct token_header {
    token_type_t type;
} token_header_t;

typedef struct token_ident {
    token_header_t header;
    const char *ident;
} token_ident_t;

typedef struct token_integer {
    token_header_t header;
    long value;
} token_integer_t;

typedef struct token_string {
    token_header_t header;
    size_t length;
    const char *data;
} token_string_t;

typedef union token {
    token_header_t header;
    token_ident_t ident;
    token_integer_t integer;
    token_string_t string;
} token_t;

typedef struct tokenizer tkn_t;

tkn_t *tkn_new();
void tkn_free(tkn_t *t);

token_t *tkn_next(tkn_t *t);
void tkn_push(tkn_t *t, token_t token);
