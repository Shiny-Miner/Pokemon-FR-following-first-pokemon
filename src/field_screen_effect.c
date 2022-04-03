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
#include "io_reg.h"
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

#define tState       data[0]

//          más hooks



void FieldCB_DefaultWarpExit(void)
{
    Overworld_PlaySpecialMapMusic();
    WarpFadeInScreen();
    SetUpWarpExitTask();

    FollowMe_WarpSetEnd();

    ScriptContext2_Enable();
}



static void Task_ExitDoor(u8 taskId)
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
        FieldSetDoorOpened(*x, *y);
        task->tState = 1;
        break;
    case 1:
        if (WaitForWeatherFadeIn())
        {
            u8 objEventId;
            SetPlayerVisibility(TRUE);
            objEventId = GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0);
            ObjectEventSetHeldMovement(&gObjectEvents[objEventId], MOVEMENT_ACTION_WALK_NORMAL_DOWN);
            task->tState = 2;
        }
        break;
    case 2:
        if (walkrun_is_standing_still())
        {
            u8 objEventId;
            task->data[1] = FieldAnimateDoorClose(*x, *y);
            objEventId = GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0);
            ObjectEventClearHeldMovementIfFinished(&gObjectEvents[objEventId]);
            task->tState = 3;
        }
        break;
    case 3:
        if (task->data[1] < 0 || gTasks[task->data[1]].isActive != TRUE)
        {
            FollowMe_SetIndicatorToComeOutDoor();
            FollowMe_WarpSetEnd();

            UnfreezeObjectEvents();
            task->tState = 4;
        }
        break;
    case 4:
        ScriptContext2_Disable();
        DestroyTask(taskId);
        break;
    }
}

static void Task_ExitNonAnimDoor(u8 taskId)
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
        if (WaitForWeatherFadeIn())
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



static void Task_SpinEnterWarp(u8 taskId)
{
    switch (gTasks[taskId].tState)
    {
    case 0:
        FreezeObjectEvents();
        ScriptContext2_Enable();
        DoPlayerSpinEntrance();
        gTasks[taskId].tState++;
        break;
    case 1:
        if (WaitForWeatherFadeIn() && IsPlayerSpinEntranceActive() != TRUE)
        {
            FollowMe_WarpSetEnd();

            UnfreezeObjectEvents();
            ScriptContext2_Disable();
            DestroyTask(taskId);
        }
        break;
    }
}





