	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000CC74 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000008C ; chunk size
	.short 16 ; number of files
	.balign 4
	.word 0x00000000, 0x00001930
	.word 0x00001930, 0x00001978
	.word 0x00001978, 0x000032A8
	.word 0x000032A8, 0x000032F0
	.word 0x000032F0, 0x00004C20
	.word 0x00004C20, 0x00004C68
	.word 0x00004C68, 0x00006598
	.word 0x00006598, 0x000065E0
	.word 0x000065E0, 0x00007F10
	.word 0x00007F10, 0x00007F58
	.word 0x00007F58, 0x00009888
	.word 0x00009888, 0x000098D0
	.word 0x000098D0, 0x0000B200
	.word 0x0000B200, 0x0000B248
	.word 0x0000B248, 0x0000CB78
	.word 0x0000CB78, 0x0000CBC0

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000CBC8 ; chunk size
	.incbin "baserom.nds", 0x1B6B4B4, 0xCBC0
	.balign 512, 255
