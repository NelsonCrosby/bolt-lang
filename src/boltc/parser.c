
#include "parser.h"

static mpc_parser_t *zparser_comment()
{
    mpc_parser_t *parser = mpc_new("comment");
    // { # ([^\n] * \n) } +
    mpc_define(
        parser,
        mpc_many1(          // (... +)
            mpcf_strfold,
            mpc_and(            // # (...)
                2, mpcf_snd,
                mpc_stripl(mpc_apply(mpc_char('#'), mpcf_free)),
                mpc_and(        // (... \n)
                    2, mpcf_strfold,
                    mpc_many(   // ([^\n] *)
                        mpcf_strfold,
                        mpc_and(
                            2, mpcf_snd,
                            mpc_not(mpc_newline(), free),
                            mpc_any(),
                            mpcf_dtor_null
                        )
                    ),
                    mpc_newline(),  // (\n)
                    free
                ),
                free
            )
        )
    );
    return parser;
}

mpc_parser_t *zparser_new()
{
    return mpc_whole(zparser_comment(), free);
}
