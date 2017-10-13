#pragma once

#include <stdlib.h>

typedef enum token_type {
    TOKEN_COMMENT = 1,

    TOKEN_VALUE = 0x20,
    TOKEN_VINT,
    TOKEN_VFLOAT,
    TOKEN_VSTRING,
    _TOKEN_VALUE_MAX,

    TOKEN_IDENT = 0x40,

    TOKEN_KW = 0x80,
    TOKEN_KW_DO,
    TOKEN_KW_WITH,
    TOKEN_KW_THEN,
    TOKEN_KW_END,
    TOKEN_KW_STRUCT,
    TOKEN_KW_INTERFACE,
    TOKEN_KW_IF,
    TOKEN_KW_ELIF,
    TOKEN_KW_ELSE,
    TOKEN_KW_WHILE,
    TOKEN_KW_FOR,
    TOKEN_KW_LET,
    TOKEN_KW_RETURN,
    TOKEN_KW_GOTO,
    TOKEN_KW_BREAK,
    TOKEN_KW_CONTINUE,
    _TOKEN_KW_MAX,

    TOKEN_KWV = 0xA0,
    TOKEN_KWV_NIL,
    TOKEN_KWV_TRUE,
    TOKEN_KWV_FALSE,
    _TOKEN_KWV_MAX,

    TOKEN_KWI = 0xC0,
    TOKEN_KWI_REF,
    TOKEN_KWI_PTR,
    TOKEN_KWI_AND,
    TOKEN_KWI_OR,
    TOKEN_KWI_XOR,
    TOKEN_KWI_NOT,
    TOKEN_KWI_IN,
    TOKEN_KWI_AS,
    _TOKEN_KWI_MAX,

    TOKEN_OP = 0x0100,
    TOKEN_OP_ASSIGN,        // =
    TOKEN_OP_DECL,          // :
    TOKEN_OP_DECL_ASSIGN,   // :=
    TOKEN_OP_EQ,            // ==
    TOKEN_OP_NEQ,           // !=
    TOKEN_OP_LT,            // <
    TOKEN_OP_LE,            // <=
    TOKEN_OP_GT,            // >
    TOKEN_OP_GE,            // >=
    TOKEN_OP_ADD,           // +
    TOKEN_OP_SUB,           // -
    TOKEN_OP_MUL,           // *
    TOKEN_OP_DIV,           // /
    _TOKEN_OP_MAX,

    TOKEN_PAREN = 0x0200,
    TOKEN_PAREN_OPEN,
    TOKEN_PAREN_CLOSE
} token_type_t;

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
