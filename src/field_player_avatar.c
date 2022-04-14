#include "global.h"
#include "main.h"
#include "bike.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_effect.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "menu.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "party_menu.h"
#include "random.h"
//#include "rotating_gate.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "task.h"
//#include "tv.h"
#include "follow_me.h"
#include "wild_encounter.h"
#include "constants/abilities.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"
#include "constants/field_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/trainer_types.h"
#define NUM_FORCED_MOVEMENTS 18
#define NUM_ACRO_BIKE_COLLISIONS 5


//static 
extern u8 CheckForPlayerAvatarCollision(u8 direction);
extern void Task_StopSurfingInit(u8 taskId);

/**
 * ::ACIMUT::
 * 2022/04/14
 * 
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Función llamada a través de una tabla:
 * - Sólo hay que cambiar el puntero.
 */


void PlayerNotOnBikeMoving(u8 direction, u16 heldKeys)
{
    u8 collision = CheckForPlayerAvatarCollision(direction);

    if (collision)
    {
        if (collision == COLLISION_LEDGE_JUMP)
        {
            PlayerJumpLedge(direction);
        }
        else if (collision == COLLISION_DIRECTIONAL_STAIR_WARP)
        {
            PlayerFaceDirection(direction);
        }
        else if (collision != COLLISION_STOP_SURFING
              && collision != COLLISION_LEDGE_JUMP
              && collision != COLLISION_PUSHED_BOULDER
              && collision != COLLISION_DIRECTIONAL_STAIR_WARP)
        {
            PlayerNotOnBikeCollide(direction);
        }
        return;
    }
    if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_SURFING)
    {
        // same speed as running
        PlayerGoSpeed2(direction);
        return;
    }

    //if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_UNDERWATER) && (heldKeys & B_BUTTON) && FlagGet(FLAG_SYS_B_DASH)
     //&& IsRunningDisallowed(gObjectEvents[gPlayerAvatar.objectEventId].currentMetatileBehavior) == 0 && !FollowerComingThroughDoor())
    if ((heldKeys & B_BUTTON) && FlagGet(FLAG_SYS_B_DASH)
        && !IsRunningDisallowed(gObjectEvents[gPlayerAvatar.objectEventId].currentMetatileBehavior)
        && !FollowerComingThroughDoor())
    {
        if (PlayerIsMovingOnRockStairs(direction))
            PlayerRunSlow(direction);
        else
            PlayerRun(direction);
        gPlayerAvatar.flags |= PLAYER_AVATAR_FLAG_DASH;
        return;
    }
    else
    {
        if (PlayerIsMovingOnRockStairs(direction))
            PlayerGoSlow(direction);
        else
            PlayerGoSpeed1(direction);
    }
}

/**
 * ::ACIMUT::
 * 2022/04/14
 * 
 * - Es llamada en otra parte de la inyección en:
 *      overworld.c
 *      void InitObjectEventsLocal(void)
 * - No es necesario repuntear.
 */

void InitPlayerAvatar(s16 x, s16 y, u8 direction, u8 gender)
{
    struct ObjectEventTemplate playerObjEventTemplate;
    u8 objectEventId;
    struct ObjectEvent *objectEvent;
    playerObjEventTemplate.localId = OBJ_EVENT_ID_PLAYER;
    playerObjEventTemplate.graphicsId = GetPlayerAvatarGraphicsIdByStateIdAndGender(PLAYER_AVATAR_STATE_NORMAL, gender);
    playerObjEventTemplate.x = x - MAP_OFFSET;
    playerObjEventTemplate.y = y - MAP_OFFSET;
    playerObjEventTemplate.elevation = 0;
    playerObjEventTemplate.movementType = MOVEMENT_TYPE_PLAYER;
    playerObjEventTemplate.movementRangeX = 0;
    playerObjEventTemplate.movementRangeY = 0;
    playerObjEventTemplate.trainerType = TRAINER_TYPE_NONE;
    playerObjEventTemplate.trainerRange_berryTreeId = 0;
    playerObjEventTemplate.script = NULL;
    playerObjEventTemplate.flagId = 0;
    objectEventId = SpawnSpecialObjectEvent(&playerObjEventTemplate);
    objectEvent = &gObjectEvents[objectEventId];
    objectEvent->isPlayer = TRUE;
    objectEvent->warpArrowSpriteId = CreateWarpArrowSprite();
    ObjectEventTurn(objectEvent, direction);
    ClearPlayerAvatarInfo();
    gPlayerAvatar.runningState = NOT_MOVING;
    gPlayerAvatar.tileTransitionState = T_NOT_MOVING;
    gPlayerAvatar.objectEventId = objectEventId;
    gPlayerAvatar.spriteId = objectEvent->spriteId;
    gPlayerAvatar.gender = gender;
    SetPlayerAvatarStateMask(PLAYER_AVATAR_FLAG_CONTROLLABLE | PLAYER_AVATAR_FLAG_ON_FOOT);    
    CreateFollowerAvatar();
}

/**
 * ::ACIMUT::
 * 2022/04/14
 * 
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Hacer hook a toda la función.
 */

void CreateStopSurfingTask(u8 direction)
{
    u8 taskId;

    ScriptContext2_Enable();
    FreezeObjectEvents();
    Overworld_ClearSavedMusic();
    Overworld_ChangeMusicToDefault();
    gPlayerAvatar.flags &= ~PLAYER_AVATAR_FLAG_SURFING;
    gPlayerAvatar.flags |= PLAYER_AVATAR_FLAG_ON_FOOT;
    gPlayerAvatar.preventStep = TRUE;
    taskId = CreateTask(Task_StopSurfingInit, 0xFF);
    gTasks[taskId].data[0] = direction;
    Task_StopSurfingInit(taskId);

    PrepareFollowerDismountSurf();
}







