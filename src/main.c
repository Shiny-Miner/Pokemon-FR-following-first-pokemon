
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
 * COMPARAR:
 * Archivos:
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
    .4byte ScrCmd_setfollower					@ 0xe3
    .4byte ScrCmd_destroyfollower			@ 0xe4
    .4byte ScrCmd_facefollower				@ 0xe5
    .4byte ScrCmd_checkfollower				@ 0xe6
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
