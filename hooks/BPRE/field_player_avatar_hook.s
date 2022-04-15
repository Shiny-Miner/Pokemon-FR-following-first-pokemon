//  --------------------------------------
//  -----   field_player_avatar.c    -----
//  --------------------------------------


//0805b9d4 l 000000d6 PlayerNotOnBikeMoving
//d5 b9 05 08   puntero hallado en: 0x0835B81C

.org 0x0835B81C
    .word PlayerNotOnBikeMoving|1


//0805d0f8 l 0000005c CreateStopSurfingTask
.org 0x0805d0f8
.area 0x5c, 0xFF
CreateStopSurfingTask_hook:
    push    {r4, lr}
    ldr     r3, =CreateStopSurfingTask|1
    bl      bx_r3_CreateStopSurfingTask
    pop     {r4, pc}

bx_r3_CreateStopSurfingTask:
    bx      r3
.pool
.endarea

