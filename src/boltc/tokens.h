#pragma once

#include <stdlib.h>

#include "token_types.h"

typedef struct token_header {
    token_type_t type;
    enum {
        TOKEN_CATEG_VALUE = 1,
        TOKEN_CATEG_IDENT = 2,
        TOKEN_CATEG_KEYWORD = 4,
        TOKEN_CATEG_OPERATOR = 8
    } category;
} token_header_t;

typedef struct token_comment {
    token_header_t header;
    const char *body;
} token_comment_t;

typedef struct token_vint {
    token_header_t header;
    long long value;
    int size;
    enum _token_vint_repr {
        TOKEN_VINT_DEC,
        TOKEN_VINT_BIN,
        TOKEN_VINT_HEX
    } repr;
} token_vint_t;

typedef struct token_vfloat {
    token_header_t header;
    long double value;
} token_vfloat_t;

typedef struct token_vstring {
    token_header_t header;
    size_t length;
    const char *data;
} token_vstring_t;

typedef struct token_ident {
    token_header_t header;
    const char *ident;
} token_ident_t;

typedef union token {
    token_header_t header;
    token_comment_t comment;
    token_vint_t vint;
    token_vfloat_t vfloat;
    token_vstring_t vstring;
    token_ident_t ident;
    // Keywords, operators, and parens have no extra information
    // than that given in the header, so they don't need any extra
    // entries.
} token_t;

typedef struct tokenizer tkn_t;

tkn_t *tkn_new();
void tkn_free(tkn_t *t);

token_t *tkn_next(tkn_t *t);

token_t *tkn_push(tkn_t *t, token_type_t type);
token_t *tkn_push_comment(tkn_t *t, const char *comment);
token_t *tkn_push_vint(
    tkn_t *t, long long value, int size, enum _token_vint_repr repr
);
token_t *tkn_push_vfloat(tkn_t *t, long double value);
token_t *tkn_push_vstring(tkn_t *t, size_t length, const char *value);
token_t *tkn_push_ident(tkn_t *t, const char *ident);
