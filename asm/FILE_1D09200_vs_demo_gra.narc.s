	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00005180 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000054 ; chunk size
	.short 9 ; number of files
	.balign 4
	.word 0x00000000, 0x00002440
	.word 0x00002440, 0x00002668
	.word 0x00002668, 0x00002E8C
	.word 0x00002E8C, 0x000036B0
	.word 0x000036B0, 0x00003ED4
	.word 0x00003ED4, 0x00004D04
	.word 0x00004D04, 0x00004DA5
	.word 0x00004DA8, 0x00004ED9
	.word 0x00004EDC, 0x00005104

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000510C ; chunk size
	.incbin "baserom.nds", 0x1D0927C, 0x5104
	.balign 512, 255
