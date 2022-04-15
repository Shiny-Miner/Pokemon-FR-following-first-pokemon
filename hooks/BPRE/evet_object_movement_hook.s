//  ---------------------------------------
//  -----   evet_object_movement.c    -----
//  ---------------------------------------

//0805df60 g 00000024 GetObjectEventIdByLocalIdAndMap
.org 0x0805df60
.area 0x24, 0xFF
GetObjectEventIdByLocalIdAndMap_hook:
    push    {r4, lr}
    ldr     r3, =GetObjectEventIdByLocalIdAndMap|1
    bl      bx_r3_GetObjectEventIdByLocalIdAndMap
    pop     {r4, pc}
bx_r3_GetObjectEventIdByLocalIdAndMap:
    bx      r3
.pool
.endarea


//0805ed10 g 00000060 RemoveObjectEventsOutsideView
.org 0x0805ed10
.area 0x60, 0xFF
RemoveObjectEventsOutsideView_hook:
    push    {r4, lr}
    ldr     r3, =RemoveObjectEventsOutsideView|1
    bl      bx_r3_RemoveObjectEventsOutsideView
    pop     {r4, pc}

bx_r3_RemoveObjectEventsOutsideView:
    bx      r3
.pool
.endarea


//08063904 l 0000007a DoesObjectCollideWithObjectAt
.org 0x08063904
.area 0x7a, 0xFF
DoesObjectCollideWithObjectAt_hook:
    push    {r4, lr}
    ldr     r3, =DoesObjectCollideWithObjectAt|1
    bl      bx_r3_DoesObjectCollideWithObjectAt
    pop     {r4, pc}

bx_r3_DoesObjectCollideWithObjectAt:
    bx      r3
.pool
.endarea


//08063ca4 g 0000005c ObjectEventSetHeldMovement
.org 0x08063ca4
.area 0x5c, 0xFF
bx_r3_ObjectEventSetHeldMovement_hook:
    push    {r4, lr}
    ldr     r3, =ObjectEventSetHeldMovement|1
    bl      bx_r3_ObjectEventSetHeldMovement
    pop     {r4, pc}

bx_r3_ObjectEventSetHeldMovement:
    bx      r3
.pool
.endarea



