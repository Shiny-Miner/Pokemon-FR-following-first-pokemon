//  ---------------------------------------
//  -----   field_control_avatar.c    -----
//  ---------------------------------------


//0806cff4 l 000000f0 GetInteractedObjectEventScript
.org 0x0806cff4
.area 0xf0, 0xFF
GetInteractedObjectEventScript_hook:
    push    {r4, lr}
    ldr     r3, =GetInteractedObjectEventScript|1
    bl      bx_r3_GetInteractedObjectEventScript
    pop     {r4, pc}

bx_r3_GetInteractedObjectEventScript:
    bx      r3
.pool
.endarea



//0806d548 l 000000a0 GetInteractedWaterScript
.org 0x0806d548
.area 0xa0, 0xFF
GetInteractedWaterScript_hook:
    push    {r4, lr}
    ldr     r3, =GetInteractedWaterScript|1
    bl      bx_r3_GetInteractedWaterScript
    pop     {r4, pc}

bx_r3_GetInteractedWaterScript:
    bx      r3
.pool
.endarea



