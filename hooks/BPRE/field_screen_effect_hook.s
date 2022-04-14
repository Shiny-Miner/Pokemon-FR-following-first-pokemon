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




