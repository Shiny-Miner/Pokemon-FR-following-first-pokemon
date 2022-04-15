//  ------------------------------
//  -----   new_game.c    -----
//  ------------------------------

//ROM:08054B3E         BL      sub_815EE0C
//ROM:08054B42         ADD     SP, SP, #8
//ROM:08054B44         POP     {R3}
//ROM:08054B46         MOV     R8, R3
//ROM:08054B48         POP     {R4-R6}
//ROM:08054B4A         POP     {R0}
//ROM:08054B4C         BX      R0
//ROM:08054B4C @ End of function sub_8054A60


.org 0x08054B3E
    bl SetWirelessCommType0_UnusedCopy

//0800b22c g 0000001c SetWirelessCommType0_UnusedCopy
.org 0x0800b22c
SetWirelessCommType0_UnusedCopy:
.area 0x1C, 0xFF
    push    {r4, lr}
    ldr     r3, =ResetFollowerSaveBlock1|1
    bl      bx_r3_ResetFollowerSaveBlock1
    pop     {r4, pc}
bx_r3_ResetFollowerSaveBlock1:
    bx      r3

.pool
.endarea

