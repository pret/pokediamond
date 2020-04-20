	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000A234 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000044 ; chunk size
	.short 7 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00008268
	.word 0x00008268, 0x00008A8C
	.word 0x00008A8C, 0x00008CB4
	.word 0x00008CB4, 0x00009904
	.word 0x00009904, 0x00009D86
	.word 0x00009D88, 0x0000A1C6

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000A1D0 ; chunk size
	.incbin "baserom.nds", 0x49A26C, 0xA1C8
	.balign 512, 255
