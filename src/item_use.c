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
#include "quest_log.h"


/**
 * ::ACIMUT::
 * 2022/04/06
 * 
 * - Esta función en FR se conoce como:
 *      void FieldUseFunc_MachBike(u8 taskId)
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Es posible hacer hook a toda esta función.
 * - Usado en items.
 */

//static EWRAM_DATA 
extern void (*sItemUseOnFieldCB)(u8 taskId);// = NULL;

//static
extern void DisplayItemMessageInCurrentContext(u8 taskId, bool8 inField, u8 textSpeed, const u8 * str);
extern void sub_80A103C(u8 taskId);
extern void PrintNotTheTimeToUseThat(u8 taskId, bool8 inField);
//extern void sub_80A1C08(u8 taskId);

static void ItemUseOnFieldCB_Bike(u8 taskId);

#define tUsingRegisteredKeyItem  data[3]

void ItemUseOutOfBattle_Bike(u8 taskId)
{
    s16 x, y;
    u8 behavior;

    PlayerGetDestCoords(&x, &y);
    behavior = MapGridGetMetatileBehaviorAt(x, y);

    if (FlagGet(FLAG_SYS_ON_CYCLING_ROAD) == TRUE
     || MetatileBehavior_IsVerticalRail(behavior) == TRUE
     || MetatileBehavior_IsHorizontalRail(behavior) == TRUE
     || MetatileBehavior_IsIsolatedVerticalRail(behavior) == TRUE
     || MetatileBehavior_IsIsolatedHorizontalRail(behavior) == TRUE)
        DisplayItemMessageInCurrentContext(taskId, gTasks[taskId].tUsingRegisteredKeyItem, 2, gUnknown_8416451);
    else if (Overworld_IsBikingAllowed() == TRUE && !IsBikingDisallowedByPlayer() && FollowerCanBike())
    {
        sItemUseOnFieldCB = ItemUseOnFieldCB_Bike;
        sub_80A103C(taskId);
    }
    else
        PrintNotTheTimeToUseThat(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
}

/**
 * ::ACIMUT::
 * 2022/04/07
 * 
 * - Esta función en FR se conoce como:
 *      static void ItemUseOnFieldCB_Bicycle(u8 taskId)
 * - Cambio de función correspondiente a fire red.
 * - Es llamado en la función anterior.
 * - No es necesario hacer hook.
 */

static void ItemUseOnFieldCB_Bike(u8 taskId)
{
    if (!TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
        PlaySE(SE_BIKE_BELL);
    GetOnOffBike(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE);

    FollowMe_HandleBike();
    ClearPlayerHeldMovementAndUnfreezeObjectEvents();
    ScriptContext2_Disable();
    DestroyTask(taskId);
}

/**
 * ::ACIMUT::
 * 2022/04/06
 * 
 * - Esta función en FR se conoce como:
 *      bool8 CanUseEscapeRopeOnCurrMap(void)
 * - Cambio de función correspondiente a fire red.
 * - Es llamada en otra parte de la inyección.
 * - Es posible hacer hook a toda esta función.
 */

bool8 CanUseDigOrEscapeRopeOnCurMap(void)
{
    if (!CheckFollowerFlag(FOLLOWER_FLAG_CAN_LEAVE_ROUTE))
        return FALSE;
    if (gMapHeader.allowEscaping)
        return TRUE;
    else
        return FALSE;
}

/*      //es necesario hacer nada aquí xd
void ItemUseOutOfBattle_EscapeRope(u8 taskId)
{
    if (CanUseDigOrEscapeRopeOnCurMap() == TRUE)
    {
        ItemUse_SetQuestLogEvent(QL_EVENT_USED_ITEM, NULL, gSpecialVar_ItemId, gMapHeader.regionMapSectionId);
        sItemUseOnFieldCB = sub_80A1C08;
        sub_80A103C(taskId);
    }
    else
    {
        PrintNotTheTimeToUseThat(taskId, gTasks[taskId].tUsingRegisteredKeyItem);
    }
}
*/












