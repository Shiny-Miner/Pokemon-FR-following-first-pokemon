//  ----------------------------
//  -----   follow_me.c    -----
//  ----------------------------

//0807e80c l 00000174 Task_DoorWarp
//0d e8 07 08   puntero hallado en: 0x0807E4FC
//función a llamar:
//void Task_DoDoorWarp(u8 taskId)
.org 0x0807E4FC
    .word Task_DoDoorWarp|1


