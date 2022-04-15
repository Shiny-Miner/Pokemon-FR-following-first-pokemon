//  ---------------------------
//  -----   item_use.c    -----
//  ---------------------------

//cambiar los punteros de los items
//080a122c g 000000d8 FieldUseFunc_MachBike
//2d 12 0a 08   puntero hallado en: 
//0x083DDCC8
//0x083DDF04
//0x083DEE24
//función a llamar:
//void ItemUseOutOfBattle_Bike(u8 taskId)

.org 0x083DDCC8
    .word ItemUseOutOfBattle_Bike|1


.org 0x083DDF04
    .word ItemUseOutOfBattle_Bike|1


.org 0x083DEE24
    .word ItemUseOutOfBattle_Bike|1


//080a1b8c g 0000001e CanUseEscapeRopeOnCurrMap
.org 0x080a1b8c
.area 0x1e, 0xFF
CanUseEscapeRopeOnCurrMap_hook:
    push    {r4, lr}
    ldr     r3, =CanUseDigOrEscapeRopeOnCurMap|1
    bl      bx_r3_CanUseDigOrEscapeRopeOnCurMap
    pop     {r4, pc}

bx_r3_CanUseDigOrEscapeRopeOnCurMap:
    bx      r3
.pool
.endarea

