//  ----------------------------
//  -----   overworld.c    -----
//  ----------------------------


//08054dd8 l 00000068 Overworld_ResetStateAfterWhitingOut
.org 0x08054dd8
.area 0x68, 0xFF
Overworld_ResetStateAfterWhitingOut_hook:
    push    {r4, lr}
    ldr     r3, =Overworld_ResetStateAfterWhitingOut|1
    bl      bx_r3_Overworld_ResetStateAfterWhitingOut
    pop     {r4, pc}
bx_r3_Overworld_ResetStateAfterWhitingOut:
    bx      r3
.pool
.endarea


//0805644c l 0000007a DoCB1_Overworld
.org 0x0805644c
.area 0x7a, 0xFF
DoCB1_Overworld_hook:
    push    {r4, lr}
    ldr     r3, =DoCB1_Overworld|1
    bl      bx_r3_DoCB1_Overworld
    pop     {r4, pc}
bx_r3_DoCB1_Overworld:
    bx      r3
.pool
.endarea


//08056cd8 l 0000006c sub_8056CD8
.org 0x08056cd8
.area 0x6c, 0xFF
sub_8056CD8_hook:
    push    {r4, lr}
    ldr     r3, =ReturnToFieldLocal|1
    bl      bx_r3_ReturnToFieldLocal
    pop     {r4, pc}
bx_r3_ReturnToFieldLocal:
    bx      r3
.pool
.endarea


//0805709c l 00000064 mli4_mapscripts_and_other
.org 0x0805709c
.area 0x64, 0xFF
mli4_mapscripts_and_other_hook:
    push    {r4, lr}
    ldr     r3, =InitObjectEventsLocal|1
    bl      bx_r3_InitObjectEventsLocal
    pop     {r4, pc}
bx_r3_InitObjectEventsLocal:
    bx      r3
.pool
.endarea

