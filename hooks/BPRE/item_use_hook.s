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
    .word FieldUseFunc_MachBike|1


.org 0x083DDF04
    .word FieldUseFunc_MachBike|1


.org 0x083DEE24
    .word FieldUseFunc_MachBike|1


