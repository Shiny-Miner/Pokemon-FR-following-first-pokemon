#include "global.h"
#include "malloc.h"
//#include "battle_pyramid.h"
#include "berry.h"
#include "decoration.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
//#include "faraway_island.h"
#include "field_camera.h"
#include "field_effect.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
//#include "mauville_old_man.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "random.h"
#include "sprite.h"
#include "task.h"
#include "trainer_see.h"
//#include "trainer_hill.h"
#include "util.h"
#include "follow_me.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/items.h"
//#include "constants/mauville_old_man.h"
#include "constants/trainer_types.h"
#include "constants/union_room.h"
#include "constants/metatile_behaviors.h"
#include "quest_log.h"

//static 
extern u8 GetObjectEventIdByLocalIdAndMapInternal(u8, u8, u8);
extern u8 GetObjectEventIdByLocalId(u8);
extern void RemoveObjectEventIfOutsideView(struct ObjectEvent *);

// Sprite data used throughout
#define sObjEventId   data[0]
#define sTypeFuncId   data[1] // Index into corresponding gMovementTypeFuncs_* table
#define sActionFuncId data[2] // Index into corresponding gMovementActionFuncs_* table
#define sDirection    data[3]

u8 GetObjectEventIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroupId)
{
    if (localId == OBJ_EVENT_ID_FOLLOWER)
        return GetFollowerObjectId();
    else if (localId < OBJ_EVENT_ID_PLAYER)
        return GetObjectEventIdByLocalIdAndMapInternal(localId, mapNum, mapGroupId);

    return GetObjectEventIdByLocalId(localId);
}

/**
 * ::ACIMUT::
 * 2022/04/15
 * - static
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Hacer hook a esta función
 */

void RemoveObjectEventsOutsideView(void)
{
    u8 i, j;
    bool8 isActiveLinkPlayer;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        for (j = 0, isActiveLinkPlayer = FALSE; j < NELEMS(gLinkPlayerObjectEvents); j++)
        {
            if (gLinkPlayerObjectEvents[j].active && i == gLinkPlayerObjectEvents[j].objEventId)
                isActiveLinkPlayer = TRUE;
        }
        if (!isActiveLinkPlayer)
        {
            struct ObjectEvent *objectEvent = &gObjectEvents[i];

            if (objectEvent->active && !objectEvent->isPlayer && i != GetFollowerObjectId())
                RemoveObjectEventIfOutsideView(objectEvent);
        }
    }
}

/**
 * ::ACIMUT::
 * 2022/04/15
 * - static
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Hacer hook a esta función
 */

bool8 DoesObjectCollideWithObjectAt(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    u8 i;
    struct ObjectEvent *curObject;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        curObject = &gObjectEvents[i];
        if (curObject->active && curObject != objectEvent && !FollowMe_IsCollisionExempt(curObject, objectEvent))
        {            
            if ((curObject->currentCoords.x == x && curObject->currentCoords.y == y) || (curObject->previousCoords.x == x && curObject->previousCoords.y == y))
            {
                if (AreZCoordsCompatible(objectEvent->currentElevation, curObject->currentElevation))
                    return TRUE;
            }
        }
    }
    return FALSE;
}

/**
 * ::ACIMUT::
 * 2022/04/15
 * - Cambio de función correspondiente a fire red.
 * - Es llamada en otra parte de la inyección.
 * - Hacer hook a esta función
 * - No declarar en archivo LD
 */

bool8 ObjectEventSetHeldMovement(struct ObjectEvent *objectEvent, u8 movementActionId)
{
    if(sub_8112CAC() == TRUE)
        ObjectEventClearHeldMovementIfActive(objectEvent);
    else if (ObjectEventIsMovementOverridden(objectEvent))
        return TRUE;

    UnfreezeObjectEvent(objectEvent);
    objectEvent->movementActionId = movementActionId;
    objectEvent->heldMovementActive = TRUE;
    objectEvent->heldMovementFinished = FALSE;
    gSprites[objectEvent->spriteId].sActionFuncId = 0;
    FollowMe(objectEvent, movementActionId, FALSE);
    return FALSE;
}

/**
 * ::ACIMUT::
 * 2022/04/15
 * - Las siguientes funciones no existen en FR
 * - Es llamada en otra parte de la inyección,
 *      en follow_me.c
 * - No es necesario hacer hook.
 */

typedef void (*SpriteStepFunc)(struct Sprite *sprite, u8 direction);

//static 
extern void MoveCoordsInDirection(u32, s16 *, s16 *, s16, s16);
extern const SpriteStepFunc *const sSpriteStepFuncsBySpeed[];
extern const s16 sSpriteStepCountsBySpeed[];

// NEW
u16 GetMiniStepCount(u8 speed)
{
    return (u16)sSpriteStepCountsBySpeed[speed];
}

// NEW
void RunMiniStep(struct Sprite *sprite, u8 speed, u8 currentFrame)
{
    sSpriteStepFuncsBySpeed[speed][currentFrame](sprite, sprite->data[3]);
}

// NEW
bool8 PlayerIsUnderWaterfall(struct ObjectEvent *objectEvent)
{
    s16 x;
    s16 y;

    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    MoveCoordsInDirection(DIR_NORTH, &x, &y, 0, 1);
    if (MetatileBehavior_IsWaterfall(MapGridGetMetatileBehaviorAt(x, y)))
        return TRUE;

    return FALSE;
}



