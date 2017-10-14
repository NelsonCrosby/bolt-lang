

#include "tokens.h"
#include "state.h"


typedef enum _zlex_state_next_status _status;

struct zlex_state {
    _status (*step)(zlex_state_t *state);
    token_list_t *tokens;
    size_t src_len;
    const char *src;
    size_t pos_len;
    const char *pos;
};

static _status state_start(zlex_state_t *state);


zlex_state_t *zlex_state_new(token_list_t *tkl, size_t len, const char *src)
{
    zlex_state_t *state = malloc(sizeof (state));
    state->step = state_start;
    state->tokens = tkl;
    if (src)
        zlex_state_setsrc(state, len, src);
    return state;
}

void zlex_state_free(zlex_state_t *state)
{
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


static _status state_start(zlex_state_t *state)
{
    return ZLEX_STATE_INVALID;
}
