#include "global.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "gpu_regs.h"
#include "main.h"
//#include "mirage_tower.h"
#include "menu.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "trainer_pokemon_sprites.h"
#include "trig.h"
#include "util.h"
#include "follow_me.h"
#include "constants/field_effects.h"
#include "constants/event_object_movement.h"
#include "constants/metatile_behaviors.h"
//#include "constants/rgb.h"
#include "constants/songs.h"
#include "help_system.h"
#include "constants/help_system.h"
#include "event_data.h"




//static 
extern void Task_FallWarpFieldEffect(u8 taskId);

/**
 * ::ACIMUT::
 * 2022/04/14
 * - Esta función en FR se conoce como:
 *      static bool8 FallWarpEffect_7(struct Task * task)
 * - Cambio de función correspondiente a fire red.
 * - No es llamada en otra parte de la inyección.
 * - Función llamada a través de una tabla:
 * - Sólo hay que cambiar el puntero.
 */


bool8 FallWarpEffect_End(struct Task *task)
{
    s16 x, y;
    gPlayerAvatar.preventStep = FALSE;
    ScriptContext2_Disable();
    CameraObjectReset1();
    UnfreezeObjectEvents();
    InstallCameraPanAheadCallback();
    PlayerGetDestCoords(&x, &y);
    // Seafoam Islands
    if (sub_8055B38(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
    {
        VarSet(VAR_TEMP_1, 1);
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_SURFING);
        SetHelpContext(HELPCONTEXT_SURFING);
    }
    DestroyTask(FindTaskIdByFunc(Task_FallWarpFieldEffect));

    FollowMe_WarpSetEnd();

    return FALSE;
}

#define tState   data[0]
#define tGoingUp data[1]

static bool8 EscalatorWarpOut_WaitForPlayer(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!ObjectEventIsMovementOverridden(objectEvent) || ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(GetPlayerFacingDirection()));
        task->tState++;
        task->data[2] = 0;
        task->data[3] = 0;
        //if ((u8)task->tGoingUp == FALSE)

        EscalatorMoveFollower(task->data[1]);

        if ((u8)task->data[1] == FALSE)
        {
            task->tState = 4; // jump to EscalatorWarpOut_Down_Ride
        }
        PlaySE(SE_ESCALATOR);
    }
    return FALSE;
}

//#define tState data[0]
#define tDestX data[1]
#define tDestY data[2]
#define tMonId data[15]

static void SurfFieldEffect_JumpOnSurfBlob(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        ObjectEventSetGraphicsId(objectEvent, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_SURFING));
        ObjectEventClearHeldMovementIfFinished(objectEvent);
        ObjectEventSetHeldMovement(objectEvent, GetJumpSpecialMovementAction(objectEvent->movementDirection));

        FollowMe_FollowerToWater();

        gFieldEffectArguments[0] = task->tDestX;
        gFieldEffectArguments[1] = task->tDestY;
        gFieldEffectArguments[2] = gPlayerAvatar.objectEventId;
        objectEvent->fieldEffectSpriteId = FieldEffectStart(FLDEFF_SURF_BLOB);
        task->tState++;
    }
}




