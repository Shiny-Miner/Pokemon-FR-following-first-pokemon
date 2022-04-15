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
NewGameInitData_hook:
    LDR     R0, =ResetFollowerSaveBlock1|1
    BL      bx_r0
    B      0x080048AA//CallWindowFunction end func
bx_r0:
    BX      R0
.pool

