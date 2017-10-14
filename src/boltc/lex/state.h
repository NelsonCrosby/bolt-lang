#pragma once

#include "tokens.h"

typedef struct zlex_state zlex_state_t;

zlex_state_t *zlex_state_new(token_list_t *tkl, size_t len, const char *src);
void zlex_state_free(zlex_state_t *state);

void zlex_state_setsrc(zlex_state_t *state, size_t len, const char *src);

enum _zlex_state_next_status {
    ZLEX_STATE_PROCESSING,
    ZLEX_STATE_INVALID,
    ZLEX_STATE_NEWTOKEN,
    ZLEX_STATE_NONELEFT
} zlex_state_step(zlex_state_t *state);
