#include "global.h"


/**
 * ::ACIMUT::
 * 2022/03/29
 * 
 * Cambiar estas funciones como specials.
*/

// follow me script commands
#include "follow_me.h"

//EWRAM
extern u16 gSpecialVar_0x8000 = 0;
extern u16 gSpecialVar_0x8001 = 0;
extern u16 gSpecialVar_0x8002 = 0;
extern u16 gSpecialVar_0x8003 = 0;
extern u16 gSpecialVar_0x8004 = 0;
extern u16 gSpecialVar_0x8005 = 0;
extern u16 gSpecialVar_0x8006 = 0;
extern u16 gSpecialVar_0x8007 = 0;
extern u16 gSpecialVar_0x8008 = 0;
extern u16 gSpecialVar_0x8009 = 0;
extern u16 gSpecialVar_0x800A = 0;
extern u16 gSpecialVar_0x800B = 0;
extern u16 gSpecialVar_Result = 0;
extern u16 gSpecialVar_LastTalked = 0;
extern u16 gSpecialVar_Facing = 0;
extern u16 gSpecialVar_MonBoxId = 0;
extern u16 gSpecialVar_MonBoxPos = 0;
extern u16 gSpecialVar_TextColor = 0;
extern u16 gSpecialVar_PrevTextColor = 0;



//hacer hook a la tabla de specials.
void Setfollower(void)
{
    u8 localId = gSpecialVar_0x8000;
    u16 flags = gSpecialVar_0x8001;

    SetUpFollowerSprite(localId, flags);
}

bool8 ScrCmd_setfollower(struct ScriptContext *ctx)
{
    u8 localId = ScriptReadByte(ctx);
    u16 flags = ScriptReadHalfword(ctx);

    SetUpFollowerSprite(localId, flags);
    return FALSE;
}


/*

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
*/
