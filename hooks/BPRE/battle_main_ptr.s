//  ------------------------------
//  -----   battle_main.c    -----
//  ------------------------------

//08015b58 l 000000a8 ReturnFromBattleToOverworld
//59 5b 01 08   puntero hallado en:
//0x08015A68
//0x08015B2C

.org 0x08015A68
    .word ReturnFromBattleToOverworld|1

.org 0x08015B2C
    .word ReturnFromBattleToOverworld|1


