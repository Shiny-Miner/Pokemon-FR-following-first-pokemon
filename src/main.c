
#include "global.h"


//  --------------------    hooks   ---------------------
// Prototipos de hooks. Pasar luego a ensamblador.




//  ----------------------------
//  -----   follow_me.c    -----
//  ----------------------------

//0807e80c l 00000174 Task_DoorWarp
//0d e8 07 08   puntero hallado en: 0x0807E4FC
//función a llamar:
//void Task_DoDoorWarp(u8 taskId)



//  ------------------------------
//  -----   battle_main.c    -----
//  ------------------------------

//08015b58 l 000000a8 ReturnFromBattleToOverworld
//59 5b 01 08   puntero hallado en:
//0x08015A68
//0x08015B2C


//  ---------------------------------------
//  -----   evet_object_movement.c    -----
//  ---------------------------------------

extern u8 GetObjectEventIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroupId);
extern void RemoveObjectEventsOutsideView(void);
extern bool8 DoesObjectCollideWithObjectAt(struct ObjectEvent *objectEvent, s16 x, s16 y);
extern bool8 ObjectEventSetHeldMovement(struct ObjectEvent *objectEvent, u8 movementActionId);

//0805df60 g 00000024 GetObjectEventIdByLocalIdAndMap
u8 GetObjectEventIdByLocalIdAndMap_hook(u8 localId, u8 mapNum, u8 mapGroupId)
{
    return GetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroupId);
}

//0805ed10 g 00000060 RemoveObjectEventsOutsideView
void RemoveObjectEventsOutsideView_hook(void)
{
    RemoveObjectEventsOutsideView();
}

//08063904 l 0000007a DoesObjectCollideWithObjectAt
bool8 DoesObjectCollideWithObjectAt_hook(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    return DoesObjectCollideWithObjectAt(objectEvent, x, y);
}

//08063ca4 g 0000005c ObjectEventSetHeldMovement
bool8 ObjectEventSetHeldMovement_hook(struct ObjectEvent *objectEvent, u8 movementActionId)
{
    return ObjectEventSetHeldMovement(objectEvent, movementActionId);
}


//  ---------------------------------------
//  -----   field_control_avatar.c    -----
//  ---------------------------------------

extern const u8 *GetInteractedObjectEventScript(struct MapPosition *position, u8 metatileBehavior, u8 direction);
extern const u8 *GetInteractedWaterScript(struct MapPosition *unused1, u8 metatileBehavior, u8 direction);

//0806cff4 l 000000f0 GetInteractedObjectEventScript
const u8 *GetInteractedObjectEventScript_hook(struct MapPosition *position, u8 metatileBehavior, u8 direction)
{
    return GetInteractedObjectEventScript(position, metatileBehavior, direction);
}

//0806d548 l 000000a0 GetInteractedWaterScript
const u8 *GetInteractedWaterScript_hook(struct MapPosition *unused1, u8 metatileBehavior, u8 direction)
{
    return GetInteractedWaterScript(unused1, metatileBehavior, direction);
}


//  -------------------------------
//  -----   field_effect.c    -----
//  -------------------------------

//08084708 l 0000007c FallWarpEffect_7
//09 47 08 08   puntero hallado en: 0x083CC04C
//función a llamar:
//bool8 FallWarpEffect_End(struct Task *task)

//08084820 l 00000070 EscalatorWarpEffect_2
//21 48 08 08   puntero hallado en: 0x083CC054
//función a llamar:
//bool8 EscalatorWarpOut_WaitForPlayer(struct Task *task)

//08086ab4 l 0000007c UseSurfEffect_4
//b5 6a 08 08   puntero hallado en: 0x083CC160
//función a llamar:
//static void SurfFieldEffect_JumpOnSurfBlob(struct Task *task)


//  --------------------------------------
//  -----   field_player_avatar.c    -----
//  --------------------------------------

//0805b9d4 l 000000d6 PlayerNotOnBikeMoving
//d5 b9 05 08   puntero hallado en: 0x0835B81C

extern void CreateStopSurfingTask(u8 direction);

//0805d0f8 l 0000005c CreateStopSurfingTask
void CreateStopSurfingTask_hook(u8 direction)
{
    CreateStopSurfingTask(direction);
}


//  --------------------------------------
//  -----   field_screen_effect.c    -----
//  --------------------------------------

extern void FieldCB_DefaultWarpExit(void);

////0807df64 g 00000018 FieldCB_DefaultWarpExit
void FieldCB_DefaultWarpExit_hook(void)
{
    FieldCB_DefaultWarpExit();
}

//0807dfbc l 00000250 sub_807DFBC
//BD DF 07 08   puntero hallado en: 0x0807DED8
//función a llamar:
//void Task_ExitDoor(u8 taskId)

//0807e20c l 000000c0 task_map_chg_seq_0807E20C
//0D E2 07 08   puntero hallado en: 0x0807DF00
//función a llamar:
//void Task_ExitNonAnimDoor(u8 taskId)

//0807e31c l 0000005c Task_TeleportWarpIn
//1D E3 07 08   puntero hallado en: 0x0807DFB8
//función a llamar:
//void Task_SpinEnterWarp(u8 taskId)


//  ----------------------------------
//  -----   fldeff_teleport.c    -----
//  ----------------------------------

//Para esta wea también cambiar el punteros de la tabla:
//  const sFieldMoveCursorCallbacks[]

//080f66f0 g 00000040 SetUpFieldMove_Teleport
//f1 66 0f 08   puntero hallado en: 0x0845A7C0


//  ---------------------------
//  -----   item_use.c    -----
//  ---------------------------

//cambiar los punteros de los items
//080a122c g 000000d8 FieldUseFunc_MachBike
//2d 12 0a 08   puntero hallado en: 
//0x083DDCC8
//0x083DDF04
//0x083DEE24
//función a llamar:
//void ItemUseOutOfBattle_Bike(u8 taskId)

extern bool8 CanUseDigOrEscapeRopeOnCurMap(void);

//080a1b8c g 0000001e CanUseEscapeRopeOnCurrMap
bool8 CanUseEscapeRopeOnCurrMap_hook(void)
{
    return CanUseDigOrEscapeRopeOnCurMap();
}


//  -----------------------------
//  -----   party_menu.c    -----
//  -----------------------------

//Para estas weas cambiar los punteros de la tabla:
//  const sFieldMoveCursorCallbacks[]

//08124998 l 00000072 SetUpFieldMove_Surf
//99 49 12 08   puntero hallado en: 0x0845A7A8

//08124a8c l 00000022 SetUpFieldMove_Fly
//8d 4a 12 08   puntero hallado en: 0x0845A798

//08124af8 l 00000066 SetUpFieldMove_Waterfall
//f9 4a 12 08   puntero hallado en: 0x0845A7B8


//  ----------------------------
//  -----   overworld.c    -----
//  ----------------------------

extern void Overworld_ResetStateAfterWhitingOut(void);
extern void DoCB1_Overworld(u16 newKeys, u16 heldKeys);
extern bool32 ReturnToFieldLocal(u8 *state);
extern void InitObjectEventsLocal(void);


//08054dd8 l 00000068 Overworld_ResetStateAfterWhitingOut
void Overworld_ResetStateAfterWhitingOut_hook(void)
{
    Overworld_ResetStateAfterWhitingOut();
}

//0805644c l 0000007a DoCB1_Overworld
void DoCB1_Overworld_hook(u16 newKeys, u16 heldKeys)
{
    DoCB1_Overworld(newKeys, heldKeys);
}

//08056cd8 l 0000006c sub_8056CD8
bool32 sub_8056CD8_hook(u8 *state)
{
    return ReturnToFieldLocal(state);
}

//0805709c l 00000064 mli4_mapscripts_and_other
void mli4_mapscripts_and_other_hook(void)
{
    InitObjectEventsLocal();
}

//  --------------------    hooks end   --------------------

/**
 * ::ACIMUT::
 * 2022-03-29
 * 
 * Port del follow me hecho por Ghoulslash en pokeemerald:
 * https://github.com/ghoulslash/pokeemerald/tree/follow_me
 * 
 * Tasklist
 * 
 * -Comparar con pokefirered las funciones.
 * -Hacer hooks a las funciones.
 * -Hay que acomodar los nuevos comandos de script.
 * -Actualizar los pointer de los nuevos comandos.
 * -Agregar nuevos comandos field_move_scripts 
 * 
 * 
 * ARCHIVO:                     FR:     LD:    HOOK:
 * --------------------------------------------------
 * srccmd.c                     ok      ok      ~
 * overworld.c                  ok      ok      -
 * party_menu.c                 ok      ok      -
 * item_use.c                   ok      ok      -
 * fldeff_teleport.c            ok      ok      -
 * field_screen_effect.c        ok      ok      -
 * field_player_avatar.c        ok      ok      -
 * field_effect.c               ok      ok      ok
 * field_control_avatar.c       ok      ok      -
 * event_object_movement.c      ok      ok      -
 * follow_me.c                  ~       ok      ok
 * battle_main.c                ok      ok      ok
 * new_game.c                   ok      ok      ok
*/


//event.inc
/*
    
    @ sets an NPC up to follow the player
    .macro setfollower localId:req, flags:req
    .byte 0xe3
    .byte \localId
    .2byte \flags
    .endm
    
    @ remove the following NPC (assumes there will only ever be one)
    .macro destroyfollower
    .byte 0xe4
    .endm
    
    @ makes the player and follower face one another
    .macro facefollower
    .byte 0xe5
    .endm
    
    @ checks if you have a follower. returns the result to VAR_RESULT
    .macro checkfollower
    .byte 0xe6
    .endm
*/






//data/script_cmd_table.inc
/*
	.4byte ScrCmd_setfollower               @ 0xe3
	.4byte ScrCmd_destroyfollower           @ 0xe4
	.4byte ScrCmd_facefollower              @ 0xe5
	.4byte ScrCmd_checkfollower             @ 0xe6
*/







//data/scripts/field_move_scripts.inc
/*
//@@ -191,7 +191,10 @@ EventScript_UseWaterfall::
	msgbox Text_WantToWaterfall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndWaterfall
	msgbox Text_MonUsedWaterfall, MSGBOX_DEFAULT
    call FollowerIntoPlayerScript
    callnative HideFollower
	dofieldeffect FLDEFF_USE_WATERFALL
    callnative FollowMe_WarpSetEnd
	goto EventScript_EndWaterfall

//...

//@@ -219,12 +222,17 @@ EventScript_UseDive::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantDive
    copyvar 0x8004 VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToDive, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndDive
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	call FollowerIntoPlayerScript
	callnative HideFollower
	setfieldeffectargument 0, VAR_0x8004
	setfieldeffectargument 1, 1
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

//...

FollowerPositionFixScript::
	setvar 0x8000 0x0
	callnative FollowerTrainerSightingPositionFix
	compare VAR_RESULT 0xFFFF
	goto_if_eq FollowerPositionFixScriptReturn
	call WalkCall
	setvar 0x8000 0x1
	callnative FollowerTrainerSightingPositionFix
FollowerPositionFixScriptReturn:
	return
    
FollowerIntoPlayerScript::
	setvar 0x8000 0x0
	callnative FollowerIntoPlayer
	compare VAR_RESULT 0xFFFF
	goto_if_eq FollowerPositionFixScriptReturn
	setvar 0x8005 0xFE  @ follower
	call WalkCall
	setvar 0x8000 0x1
	callnative FollowerIntoPlayer
	return
    
WalkCall:
	compare VAR_RESULT 0x0
	call_if_eq WalkDownCall
	compare VAR_RESULT 0x1
	call_if_eq WalkUpCall
	compare VAR_RESULT 0x2
	call_if_eq WalkLeftCall
	compare VAR_RESULT 0x3
	call_if_eq WalkRightCall
	waitmovement 0x8005
	return
	
WalkDownCall:
	applymovement 0x8005 WalkDown
	return

WalkUpCall:
	applymovement 0x8005 WalkUp
	return

WalkLeftCall:
	applymovement 0x8005 WalkLeft
	return

WalkRightCall:
	applymovement 0x8005 WalkRight
	return
    
WalkDown:
    walk_down
    step_end 

WalkUp:
    walk_up
    step_end

WalkLeft:
    walk_left
    step_end

WalkRight:
    walk_right
    step_end
*/
