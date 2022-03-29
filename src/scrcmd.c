#include "global.h"


// follow me script commands
#include "follow_me.h"
bool8 ScrCmd_setfollower(struct ScriptContext *ctx)
{
    u8 localId = ScriptReadByte(ctx);
    u16 flags = ScriptReadHalfword(ctx);

    SetUpFollowerSprite(localId, flags);
    return FALSE;
}

/**
 * ::ACIMUT::
 * 
 * Se puede usar estas funciones como specials.
*/

bool8 ScrCmd_destroyfollower(struct ScriptContext *ctx)
{
    DestroyFollower();
    return FALSE;
}

bool8 ScrCmd_facefollower(struct ScriptContext *ctx)
{
    PlayerFaceFollowerSprite();
    return FALSE;
}

bool8 ScrCmd_checkfollower(struct ScriptContext *ctx)
{
    CheckPlayerHasFollower();
    return FALSE;
}
