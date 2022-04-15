#include "global.h"
#include "cable_club.h"
#include "event_data.h"
#include "fieldmap.h"
#include "field_camera.h"
#include "field_door.h"
#include "field_effect.h"
#include "event_object_lock.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
//#include "field_special_scene.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "gba/io_reg.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "main.h"
#include "menu.h"
//#include "mirage_tower.h"
#include "metatile_behavior.h"
#include "palette.h"
#include "overworld.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "start_menu.h"
#include "task.h"
#include "text.h"
#include "follow_me.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/songs.h"
//#include "constants/rgb.h"
//#include "trainer_hill.h"
#include "fldeff.h"
#include "field_fadetransition.h"
#include "quest_log.h"
#include "field_screen.h"


#define tState       data[0]

//static
extern void WarpFadeInScreenWithDelay(void);
extern void sub_807DE78(bool8 a0);



/**
 * ::ACIMUT::
 * 2022/04/07
 * 
 * - Esta función en FR está en field_fadetransition.c
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Hacer hook a toda esta función.
 */

void FieldCB_DefaultWarpExit(void)
{
    Overworld_PlaySpecialMapMusic();
    QuestLog_DrawPreviouslyOnQuestHeaderIfInPlaybackMode();
    sub_807DE78(FALSE);

    FollowMe_WarpSetEnd();

    ScriptContext2_Enable();
}



/**
 * ::ACIMUT::
 * 2022/04/07
 * 
 * - Esta función en FR está en field_fadetransition.c
 * - Las siguiente función sólo es llamada en:
 *              static void sub_807DE78(bool8 a0)
 * 
 * - Esta función en FR se conoce como:
 *          static void sub_807DFBC(u8 taskId)
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * 
 * - Sólo hay que cambiar un puntero.
 */

//static
void Task_ExitDoor(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    s16 *x = &task->data[2];
    s16 *y = &task->data[3];

    if (task->tState == 0)
        task->tState = 5;

    switch (task->tState)
    {
    case 0: // Never reached
        HideFollower();
        SetPlayerVisibility(FALSE);
        FreezeObjectEvents();
        PlayerGetDestCoords(x, y);
        FieldSetDoorOpened(*x, *y);
        task->tState = 1;
        break;
    case 5:
        HideFollower();
        SetPlayerVisibility(FALSE);
        FreezeObjectEvents();
        DoOutwardBarnDoorWipe();
        WarpFadeInScreenWithDelay();
        task->tState = 6;
        break;
    case 6:
        task->data[15]++;
        if (task->data[15] == 25)
        {
            PlayerGetDestCoords(x, y);
            PlaySE(GetDoorSoundEffect(*x, *y));
            FieldAnimateDoorOpen(*x, *y);
            task->tState = 7;
        }
        break;
    case 7:
        if (!FieldIsDoorAnimationRunning())
        {
            PlayerGetDestCoords(&task->data[12], &task->data[13]);
            SetPlayerVisibility(TRUE);
            ObjectEventSetHeldMovement(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)], MOVEMENT_ACTION_WALK_NORMAL_DOWN);
            task->tState = 8;
        }
        break;
    case 8:
        task->data[14]++;
        if (task->data[14] == 14)
        {
            FieldAnimateDoorClose(task->data[12], task->data[13]);
            task->tState = 9;
        }
        break;
    case 9:
        if (FieldFadeTransitionBackgroundEffectIsFinished() && walkrun_is_standing_still() && !FieldIsDoorAnimationRunning() && !FuncIsActiveTask(Task_BarnDoorWipe))
        {
            ObjectEventClearHeldMovementIfFinished(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)]);
            task->tState = 4;
        }
        break;
    // Legacy RS
    case 1:
        if (FieldFadeTransitionBackgroundEffectIsFinished())
        {
            SetPlayerVisibility(TRUE);
            ObjectEventSetHeldMovement(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)], MOVEMENT_ACTION_WALK_NORMAL_DOWN);
            task->tState = 2;
        }
        break;
    case 2:
        if (walkrun_is_standing_still())
        {
            task->data[1] = FieldAnimateDoorClose(*x, *y);
            ObjectEventClearHeldMovementIfFinished(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)]);
            task->tState = 3;
        }
        break;
    case 3:
        if (task->data[1] < 0 || gTasks[task->data[1]].isActive != TRUE)
            task->tState = 4;
        break;
    case 4:
        FollowMe_SetIndicatorToComeOutDoor();
        FollowMe_WarpSetEnd();
        UnfreezeObjectEvents();
        ScriptContext2_Disable();
        DestroyTask(taskId);
        break;
    }
}

/**
 * ::ACIMUT::
 * 2022/04/07
 * 
 * - Esta función en FR está en field_fadetransition.c
 * - Las siguiente función sólo es llamada en:
 *              static void sub_807DE78(bool8 a0)
 * 
 * - Esta función en FR se conoce como:
 *          static void task_map_chg_seq_0807E20C(u8 taskId)
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * 
 * - Sólo hay que cambiar un puntero.
 */

//static 
void Task_ExitNonAnimDoor(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s16 *x = &task->data[2];
    s16 *y = &task->data[3];
    switch (task->tState)
    {
    case 0:
        HideFollower();
        SetPlayerVisibility(FALSE);
        FreezeObjectEvents();
        PlayerGetDestCoords(x, y);
        task->tState = 1;
        break;
    case 1:
        if (FieldFadeTransitionBackgroundEffectIsFinished())
        {
            u8 objEventId;
            SetPlayerVisibility(TRUE);
            objEventId = GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0);
            ObjectEventSetHeldMovement(&gObjectEvents[objEventId], GetWalkNormalMovementAction(GetPlayerFacingDirection()));
            task->tState = 2;
        }
        break;
    case 2:
        if (walkrun_is_standing_still())
        {
            FollowMe_SetIndicatorToComeOutDoor();
            FollowMe_WarpSetEnd();

            UnfreezeObjectEvents();
            task->tState = 3;
        }
        break;
    case 3:
        ScriptContext2_Disable();
        DestroyTask(taskId);
        break;
    }
}

/**
 * ::ACIMUT::
 * 2022/04/07
 * 
 * - Esta función en FR está en field_fadetransition.c
 * - Las siguiente función sólo es llamada en:
 *              static void FieldCB_TeleportWarpIn(void)
 * 
 * - Esta función en FR se conoce como:
 *          static void Task_TeleportWarpIn(u8 taskId)
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * 
 * - Sólo hay que cambiar un puntero.
 */

//static 
void Task_SpinEnterWarp(u8 taskId)
{
    switch (gTasks[taskId].tState)
    {
    case 0:
        FreezeObjectEvents();
        ScriptContext2_Enable();
        StartTeleportInPlayerAnim();
        gTasks[taskId].tState++;
        break;
    case 1:
        if (FieldFadeTransitionBackgroundEffectIsFinished() && WaitTeleportInPlayerAnim() != TRUE)
        {
            FollowMe_WarpSetEnd();

            UnfreezeObjectEvents();
            ScriptContext2_Disable();
            DestroyTask(taskId);
        }
        break;
    }
}





