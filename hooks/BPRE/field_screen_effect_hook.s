//  --------------------------------------
//  -----   field_screen_effect.c    -----
//  --------------------------------------


//0807dfbc l 00000250 sub_807DFBC
//BD DF 07 08   puntero hallado en: 0x0807DED8
//función a llamar:
//void Task_ExitDoor(u8 taskId)

.org 0x0807DED8
    .word Task_ExitDoor|1



//0807e20c l 000000c0 task_map_chg_seq_0807E20C
//0D E2 07 08   puntero hallado en: 0x0807DF00
//función a llamar:
//void Task_ExitNonAnimDoor(u8 taskId)

.org 0x0807DF00
    .word Task_ExitNonAnimDoor|1




//0807e31c l 0000005c Task_TeleportWarpIn
//1D E3 07 08   puntero hallado en: 0x0807DFB8
//función a llamar:
//void Task_SpinEnterWarp(u8 taskId)

.org 0x0807DFB8
    .word Task_SpinEnterWarp|1


//0807df64 g 00000018 FieldCB_DefaultWarpExit
.org 0x0807df64
.area 0x18, 0xFF
FieldCB_DefaultWarpExit_hook:
    push    {r4, lr}
    ldr     r3, =FieldCB_DefaultWarpExit|1
    bl      bx_r3_FieldCB_DefaultWarpExit
    pop     {r4, pc}

bx_r3_FieldCB_DefaultWarpExit:
    bx      r3
.pool
.endarea


