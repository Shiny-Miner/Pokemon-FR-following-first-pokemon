//  -------------------------------
//  -----   field_effect.c    -----
//  -------------------------------

//08084708 l 0000007c FallWarpEffect_7
//09 47 08 08   puntero hallado en: 0x083CC04C
//función a llamar:
//bool8 FallWarpEffect_End(struct Task *task)

.org 0x083CC04C
    .word FallWarpEffect_End|1



//08084820 l 00000070 EscalatorWarpEffect_2
//21 48 08 08   puntero hallado en: 0x083CC054
//función a llamar:
//bool8 EscalatorWarpOut_WaitForPlayer(struct Task *task)

.org 0x083CC054
      .word EscalatorWarpOut_WaitForPlayer|1


//08086ab4 l 0000007c UseSurfEffect_4
//b5 6a 08 08   puntero hallado en: 0x083CC160
//función a llamar:
//static void SurfFieldEffect_JumpOnSurfBlob(struct Task *task)

.org 0x083CC160
   .word SurfFieldEffect_JumpOnSurfBlob|1






