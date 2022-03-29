#include "global.h"
#include "overworld.h"
//#include "battle_pyramid.h"
#include "battle_setup.h"
#include "berry.h"
#include "bg.h"
#include "cable_club.h"
//#include "clock.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_camera.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_message_box.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
//#include "field_special_scene.h"
#include "field_specials.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "gpu_regs.h"
#include "heal_location.h"
#include "io_reg.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "main.h"
#include "malloc.h"
#include "m4a.h"
#include "map_name_popup.h"
//#include "match_call.h"
#include "menu.h"
#include "metatile_behavior.h"
//#include "mirage_tower.h"
#include "money.h"
#include "new_game.h"
#include "palette.h"
#include "play_time.h"
#include "random.h"
#include "roamer.h"
//#include "rotating_gate.h"
#include "safari_zone.h"
#include "save.h"
#include "save_location.h"
#include "script.h"
#include "script_pokemon_util.h"
//#include "secret_base.h"
#include "sound.h"
#include "start_menu.h"
#include "task.h"
#include "tileset_anims.h"
//#include "time_events.h"
//#include "trainer_hill.h"
#include "trainer_pokemon_sprites.h"
//#include "tv.h"
#include "scanline_effect.h"
#include "wild_encounter.h"
//#include "frontier_util.h"
#include "follow_me.h"
#include "constants/abilities.h"
#include "constants/layouts.h"
#include "constants/map_types.h"
#include "constants/region_map_sections.h"
#include "constants/songs.h"
//#include "constants/trainer_hill.h"
#include "constants/weather.h"
#include "constants/event_object_movement.h"



static void Overworld_ResetStateAfterWhiteOut(void)
{
    ResetInitialPlayerAvatarState();
    FlagClear(FLAG_SYS_CYCLING_ROAD);
    FlagClear(FLAG_SYS_CRUISE_MODE);
    FlagClear(FLAG_SYS_SAFARI_MODE);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_USE_FLASH);
    // If you were defeated by Kyogre/Groudon and the step counter has
    // maxed out, end the abnormal weather.
    if (VarGet(VAR_SHOULD_END_ABNORMAL_WEATHER) == 1)
    {
        VarSet(VAR_SHOULD_END_ABNORMAL_WEATHER, 0);
        VarSet(VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_NONE);
    }

    FollowMe_TryRemoveFollowerOnWhiteOut();
}


static void DoCB1_Overworld(u16 newKeys, u16 heldKeys)
{
    struct FieldInput inputStruct;
    UpdatePlayerAvatarTransitionState();
    FieldClearPlayerInput(&inputStruct);
    FieldGetPlayerInput(&inputStruct, newKeys, heldKeys);
    if (!ScriptContext2_IsEnabled())
    {
        if (ProcessPlayerFieldInput(&inputStruct) == 1)
        {
            ScriptContext2_Enable();
            HideMapNamePopUpWindow();
        }
        else
        {
            PlayerStep(inputStruct.dpadDirection, newKeys, heldKeys);
        }
    }

    // if stop running but keep holding B -> fix follower frame
    if (PlayerHasFollower() && IsPlayerOnFoot() && IsPlayerStandingStill())
        ObjectEventSetHeldMovement(&gObjectEvents[GetFollowerObjectId()], GetFaceDirectionAnimNum(gObjectEvents[GetFollowerObjectId()].facingDirection));
}



static bool32 ReturnToFieldLocal(u8 *state)
{
    switch (*state)
    {
    case 0:
        ResetMirageTowerAndSaveBlockPtrs();
        ResetScreenForMapLoad();
        ResumeMap(FALSE);
        InitObjectEventsReturnToField();
        SetCameraToTrackPlayer();
        (*state)++;
        break;
    case 1:
        InitViewGraphics();
        TryLoadTrainerHillEReaderPalette();
        FollowMe_BindToSurbBlobOnReloadScreen();
        (*state)++;
        break;
    case 2:
        if (RunFieldCallback())
            (*state)++;
        break;
    case 3:
        return TRUE;
    }
    return FALSE;
}


static void InitObjectEventsLocal(void)
{
    s16 x, y;
    struct InitialPlayerAvatarState *player;
    gTotalCameraPixelOffsetX = 0;
    gTotalCameraPixelOffsetY = 0;
    ResetObjectEvents();
    GetCameraFocusCoords(&x, &y);
    player = GetInitialPlayerAvatarState();
    InitPlayerAvatar(x, y, player->direction, gSaveBlock2Ptr->playerGender);
    SetPlayerAvatarTransitionFlags(player->transitionFlags);
    ResetInitialPlayerAvatarState();
    TrySpawnObjectEvents(0, 0);
    TryRunOnWarpIntoMapScript();

    FollowMe_HandleSprite();
}





