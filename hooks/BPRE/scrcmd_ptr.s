//  --------------------------
//  -----   srccmd.c    -----
//  --------------------------

//Se hace uso de la tabla de specials.
//0815fd60 g 00000000 gSpecials

definelabel gSpecials 0x0815fd60

.org gSpecials + (4 * 0x10)
    .word Setfollower|1
    .word DestroyFollower
    .word PlayerFaceFollowerSprite|1
    .word CheckPlayerHasFollower|1

