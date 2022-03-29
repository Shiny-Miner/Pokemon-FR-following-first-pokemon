#include "global.h"

/**
 * Mover esta función a follow_me.c
*/

u8* ReadWord(u8 index)
{
    struct ScriptContext *ctx = &sScriptContext1;

    return (T1_READ_PTR(&ctx->data[index]));
}
