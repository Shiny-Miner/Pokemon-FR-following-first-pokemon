#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_gfx_sfx_util.h"
#include "battle_interface.h"
//#include "battle_pike.h"
//#include "battle_pyramid.h"
//#include "battle_pyramid_bag.h"
#include "bg.h"
//#include "contest.h"
#include "data.h"
#include "decompress.h"
#include "easy_chat.h"
#include "event_data.h"
#include "evolution_scene.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_specials.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
//#include "fldeff_misc.h"
//#include "frontier_util.h"
#include "gpu_regs.h"
#include "graphics.h"
//#include "international_string_util.h"
#include "item.h"
#include "item_menu.h"
#include "item_use.h"
#include "link.h"
#include "link_rfu.h"
#include "mail.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
//#include "menu_specialized.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "player_pc.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_jump.h"
#include "pokemon_storage_system.h"
#include "pokemon_summary_screen.h"
#include "region_map.h"
#include "reshow_battle_screen.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "start_menu.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "trade.h"
#include "union_room.h"
#include "window.h"
#include "follow_me.h"
#include "constants/battle.h"
//#include "constants/battle_frontier.h"
#include "constants/field_effects.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
//#include "constants/rgb.h"
#include "constants/songs.h"
#define PARTY_PAL_SELECTED     (1 << 0)
#define PARTY_PAL_FAINTED      (1 << 1)
#define PARTY_PAL_TO_SWITCH    (1 << 2)
#define PARTY_PAL_MULTI_ALT    (1 << 3)
#define PARTY_PAL_SWITCHING    (1 << 4)
#define PARTY_PAL_TO_SOFTBOIL  (1 << 5)
#define PARTY_PAL_NO_MON       (1 << 6)
#define PARTY_PAL_UNUSED       (1 << 7)
#define MENU_DIR_DOWN     1
#define MENU_DIR_UP      -1
#define MENU_DIR_RIGHT    2
#define MENU_DIR_LEFT    -2


extern void FieldCallback_Surf(void);
extern void FieldCallback_Waterfall(void);

/**
 * ::ACIMUT::
 * 2022/04/06
 * 
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Cambiar puntero de esta función, declarada 
 *      en party_menu.h en la siguiente tabla:
 *      const sFieldMoveCursorCallbacks[]
 */

//static 
bool8 SetUpFieldMove_Surf(void)
{
    s16 x, y;

    if (!CheckFollowerFlag(FOLLOWER_FLAG_CAN_SURF))
        return FALSE;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    if (MetatileBehavior_IsSemiDeepWater(MapGridGetMetatileBehaviorAt(x, y)) != TRUE
     && PartyHasMonWithSurf() == TRUE
     && IsPlayerFacingSurfableFishableWater() == TRUE)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Surf;
        return TRUE;
    }
    return FALSE;
}


//static 
bool8 SetUpFieldMove_Fly(void)
{
    if (!CheckFollowerFlag(FOLLOWER_FLAG_CAN_LEAVE_ROUTE))
        return FALSE;

    if (Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE)
        return TRUE;
    else
        return FALSE;
}

//static 
bool8 SetUpFieldMove_Waterfall(void)
{
    s16 x, y;

    if (!CheckFollowerFlag(FOLLOWER_FLAG_CAN_WATERFALL))
        return FALSE;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    if (MetatileBehavior_IsWaterfall(MapGridGetMetatileBehaviorAt(x, y)) == TRUE && IsPlayerSurfingNorth() == TRUE)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Waterfall;
        return TRUE;
    }
    return FALSE;
}

/*          //no está en Fire Red.
extern void FieldCallback_Dive(void);
//static void FieldCallback_Dive(void)
//{
//    gFieldEffectArguments[0] = GetCursorSelectionMonId();
//    FieldEffectStart(FLDEFF_USE_DIVE);
//}


static bool8 SetUpFieldMove_Dive(void)
{
    if (!CheckFollowerFlag(FOLLOWER_FLAG_CAN_DIVE))
        return FALSE;

    gFieldEffectArguments[1] = TrySetDiveWarp();
    if (gFieldEffectArguments[1] != 0)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Dive;
        return TRUE;
    }
    return FALSE;
}
*/



