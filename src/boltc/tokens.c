
#include <stdlib.h>

#include "tokens.h"


struct token_list_node {
    token_t *token;
    struct token_list_node *next;
};

struct token_list {
    struct token_list_node *first;
    struct token_list_node *last;
    token_t *prev;
};

struct tokenizer {
    struct token_list tokens;
};


tkn_t *tkn_new()
{
    tkn_t *t = malloc(sizeof (t));
    t->tokens.first = NULL;
    t->tokens.last = NULL;
    t->tokens.prev = NULL;
    return t;
}

void tkn_free(tkn_t *t)
{
    free(t);
}

token_t *tkn_next(tkn_t *t)
{
    if (t->tokens.prev) {
        free(t->tokens.prev);
        t->tokens.prev = NULL;
    }
    struct token_list_node *node = t->tokens.first;
    if (node) {
        token_t *token = node->token;
        t->tokens.first = node->next;
        free(node);
        t->tokens.prev = token;
        return token;
    } else {
        return NULL;
    }
}

void tkn_push(tkn_t *t, token_t token)
{
    struct token_list_node *node = malloc(sizeof (node));
    node->token = malloc(sizeof (node->token));
    *node->token = token;
    node->next = NULL;

    if (!t->tokens.first) {
        t->tokens.first = node;
    }

    if (t->tokens.last) {
        t->tokens.last->next = node;
    } else {
        t->tokens.last = node;
    }

    t->tokens.last = node;
}
