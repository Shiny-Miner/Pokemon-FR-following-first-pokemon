.gba
.thumb
.open "BPRE.gba","build/rom_BPRE.gba", 0x08000000
//---------------------------------------------------
//          hooks

.include "hooks/BPRE/battle_main_ptr.s"
.include "hooks/BPRE/evet_object_movement_hook.s"
.include "hooks/BPRE/field_control_avatar_hook.s"
.include "hooks/BPRE/field_effect_hook.s"
.include "hooks/BPRE/field_player_avatar_hook.s"
.include "hooks/BPRE/field_screen_effect_hook.s"
.include "hooks/BPRE/fldeff_teleport_hook.s"
.include "hooks/BPRE/follow_me_ptr.s"
.include "hooks/BPRE/item_use_hook.s"
.include "hooks/BPRE/new_game_hook.s"
.include "hooks/BPRE/overworld_hook.s"
.include "hooks/BPRE/party_menu_hook.s"
.include "hooks/BPRE/scrcmd_ptr.s"


//---------------------------------------------------
.align 4
.org insertinto
.importobj "build/linked.o"
.close
