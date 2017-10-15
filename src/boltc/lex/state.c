
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "state.h"


#define STB_ANY                 32
#define STC_LCOMMENT_START      '#'
#define STC_LCOMMENT_END        '\n'
#define STB_LCOMMENT            80
#define STC_VSTRING_START       '"'
#define STC_VSTRING_END         '"'
#define STC_VSTRING_ESC         '\\'
#define STB_VSTRING             80


typedef enum _zlex_state_next_status _status;

struct zlex_state {
    _status (*step)(zlex_state_t *state);
    token_list_t *tokens;
    size_t src_len;
    const char *src;
    size_t pos_len;
    const char *pos;
    size_t cpy_len, cpy_size;
    char *cpy;
};

static _status state_start(zlex_state_t *state);
static _status state_comment(zlex_state_t *state);
static _status state_vstring(zlex_state_t *state);


zlex_state_t *zlex_state_new(token_list_t *tkl, size_t len, const char *src)
{
    zlex_state_t *state = malloc(sizeof (*state));
    state->step = state_start;
    state->tokens = tkl;
    zlex_state_setsrc(state, len, src);
    state->cpy_len = state->cpy_size = 0;
    state->cpy = NULL;
    return state;
}

void zlex_state_free(zlex_state_t *state)
{
    if (state->cpy)
        free(state->cpy);
    free(state);
}

void zlex_state_setsrc(zlex_state_t *state, size_t len, const char *src)
{
    state->src_len = state->pos_len = len;
    state->src = state->pos = src;
}

_status zlex_state_step(zlex_state_t *state)
{
    return state->step(state);
}


// Increment to next character
static char _nc(zlex_state_t *state)
{
    --state->pos_len;
    return *(++state->pos);
}

static void _cpy_null(zlex_state_t *state)
{
    state->cpy = NULL;
    state->cpy_len = state->cpy_size = 0;
}
static void _cpy_free(zlex_state_t *state)
{
    free(state->cpy);
    _cpy_null(state);
}
static void _cpy_alloc(zlex_state_t *state, size_t sz)
{
    if (state->cpy)
        _cpy_free(state);
    state->cpy_len = 0;
    state->cpy_size = sz;
    state->cpy = malloc(sizeof (char) * sz);
}
static void _cpy_grow(zlex_state_t *state, size_t by)
{
    if (by == 0)
        by = state->cpy_size;
    
    state->cpy = realloc(state->cpy, state->cpy_size += by);
}
static void _cpy_append(zlex_state_t *state, char c)
{
    if (!state->cpy)
        _cpy_alloc(state, STB_ANY);
    if (state->cpy_len == state->cpy_size)
        _cpy_grow(state, 0);
    state->cpy[state->cpy_len++] = c;
}
static void _cpy_appends(zlex_state_t *state, size_t len, const char *s)
{
    if (!state->cpy)
        _cpy_alloc(state, len);
    size_t space = state->cpy_size - state->cpy_len;
    if (space < len)
        _cpy_grow(state, len - space);
    memcpy(state->cpy + state->cpy_len, s, len);
    state->cpy_len += len;
}


static _status state_start(zlex_state_t *state)
{
    // Ignore whitespace
    for (char c = *state->pos;
            state->pos_len && (c == ' ' || c == '\t' || c == '\n');
            c = _nc(state)) {}
    if (!state->pos_len)
        return ZLEX_STATE_NONELEFT;

    // TODO: Pick up on keywords?

    switch (*state->pos) {
    case STC_LCOMMENT_START:
        state->step = state_comment;
        _cpy_alloc(state, STB_LCOMMENT);
        return ZLEX_STATE_PROCESSING;
    case STC_VSTRING_START:
        state->step = state_vstring;
        _cpy_alloc(state, STB_VSTRING);
        return ZLEX_STATE_PROCESSING;
    default:
        return ZLEX_STATE_INVALID;
    }
}

static _status state_comment(zlex_state_t *state)
{
    if (!state->pos_len)
        return ZLEX_STATE_NONELEFT;

    char c = _nc(state);
    if (c == STC_LCOMMENT_END) {
        _cpy_append(state, '\0');
        tkl_push_comment(state->tokens, state->cpy);
        _cpy_null(state);
        state->step = state_start;
        return ZLEX_STATE_NEWTOKEN;
    } else {
        _cpy_append(state, c);
        return ZLEX_STATE_PROCESSING;
    }
}

static _status state_vstring(zlex_state_t *state)
{
    if (!state->pos_len)
        return ZLEX_STATE_NONELEFT;
    
    char c = _nc(state);
    if (c == STC_VSTRING_END) {
        _nc(state);
        _cpy_append(state, '\0');
        tkl_push_vstring(state->tokens, state->cpy_len, state->cpy);
        _cpy_null(state);
        state->step = state_start;
        return ZLEX_STATE_NEWTOKEN;
    } else if (c == STC_VSTRING_ESC) {
        switch (_nc(state)) {
        case STC_VSTRING_ESC:
            _cpy_append(state, STC_VSTRING_ESC);
            break;
        case STC_VSTRING_END:
            _cpy_append(state, STC_VSTRING_END);
            break;
        case 'n':
            _cpy_append(state, '\n');
            break;
        case 't':
            _cpy_append(state, '\t');
            break;
        default:
            return ZLEX_STATE_INVALID;
        }
        return ZLEX_STATE_PROCESSING;
    } else if (c == '\n') {
        return ZLEX_STATE_INVALID;
    } else {
        _cpy_append(state, c);
        return ZLEX_STATE_PROCESSING;
    }
}
