.gba
.thumb
.open "BPRS.gba","build/rom_BPRS.gba", 0x08000000
//---------------------------------------------------
.align 4
.org insertinto
.importobj "build/linked.o"
.close
