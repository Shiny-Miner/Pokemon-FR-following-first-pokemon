#include "global.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fldeff.h"
#include "party_menu.h"
#include "overworld.h"
#include "task.h"
#include "follow_me.h"
#include "constants/field_effects.h"

extern void FieldCallback_Teleport(void);
//static void StartTeleportFieldEffect(void);

bool8 SetUpFieldMove_Teleport(void)
{
    if (!CheckFollowerFlag(FOLLOWER_FLAG_CAN_LEAVE_ROUTE))
        return FALSE;

    if (Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Teleport;
        return TRUE;
    }
    return FALSE;
}



