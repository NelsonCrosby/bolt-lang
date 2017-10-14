#pragma once

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

        TOKEN_OP_ACCESS,        // .

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

        TOKEN_OP_BAND,          // &
        TOKEN_OP_BOR,           // |
        TOKEN_OP_BXOR,          // ^
        TOKEN_OP_BNOT,          // ~
        TOKEN_OP_SHL,           // <<
        TOKEN_OP_SHR,           // >>

    _TOKEN_OP_MAX,

    TOKEN_PAREN = 0x0200,
    TOKEN_PAREN_OPEN,
    TOKEN_PAREN_CLOSE,
    TOKEN_RPAREN_OPEN,
    TOKEN_RPAREN_CLOSE
} token_type_t;
