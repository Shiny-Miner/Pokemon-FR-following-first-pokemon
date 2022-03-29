#include "global.h"
#include "item_use.h"
#include "battle.h"
//#include "battle_pyramid.h"
//#include "battle_pyramid_bag.h"
#include "berry.h"
#include "berry_powder.h"
#include "bike.h"
#include "coins.h"
#include "data.h"
#include "event_data.h"
#include "event_object_lock.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "item.h"
#include "item_menu.h"
#include "item_use.h"
#include "mail.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
//#include "pokeblock.h"
#include "pokemon.h"
#include "script.h"
#include "sound.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "follow_me.h"
#include "constants/event_bg.h"
#include "constants/event_objects.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/songs.h"


void ItemUseOutOfBattle_Bike(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    s16 coordsY;
    s16 coordsX;
    u8 behavior;
    PlayerGetDestCoords(&coordsX, &coordsY);
    behavior = MapGridGetMetatileBehaviorAt(coordsX, coordsY);
    if (FlagGet(FLAG_SYS_CYCLING_ROAD) == TRUE || MetatileBehavior_IsVerticalRail(behavior) == TRUE || MetatileBehavior_IsHorizontalRail(behavior) == TRUE || MetatileBehavior_IsIsolatedVerticalRail(behavior) == TRUE || MetatileBehavior_IsIsolatedHorizontalRail(behavior) == TRUE)
        DisplayCannotDismountBikeMessage(taskId, tUsingRegisteredKeyItem);
    else
    {
        //if (Overworld_IsBikingAllowed() == TRUE && IsBikingDisallowedByPlayer() == 0)
        if (Overworld_IsBikingAllowed() == TRUE && IsBikingDisallowedByPlayer() == 0 && FollowerCanBike())
        {
            sItemUseOnFieldCB = ItemUseOnFieldCB_Bike;
            SetUpItemUseOnFieldCallback(taskId);
        }
        else
            DisplayDadsAdviceCannotUseItemMessage(taskId, tUsingRegisteredKeyItem);
    }
}
static void ItemUseOnFieldCB_Bike(u8 taskId)
{
    if (ItemId_GetSecondaryId(gSpecialVar_ItemId) == MACH_BIKE)
        GetOnOffBike(PLAYER_AVATAR_FLAG_MACH_BIKE);
    else
        GetOnOffBike(PLAYER_AVATAR_FLAG_ACRO_BIKE);

    FollowMe_HandleBike();
    ScriptUnfreezeObjectEvents();
    ScriptContext2_Disable();
    DestroyTask(taskId);
}


bool8 CanUseDigOrEscapeRopeOnCurMap(void)
{
    if (!CheckFollowerFlag(FOLLOWER_FLAG_CAN_LEAVE_ROUTE))
        return FALSE;
    if (gMapHeader.allowEscaping)
        return TRUE;
    else
        return FALSE;
}
void ItemUseOutOfBattle_EscapeRope(u8 taskId)
{
    if (CanUseDigOrEscapeRopeOnCurMap() == TRUE)
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_EscapeRope;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
}













