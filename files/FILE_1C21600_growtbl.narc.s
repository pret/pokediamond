	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000D14 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000004C ; chunk size
	.short 8 ; number of files
	.balign 4
	.word 0x00000000, 0x00000194
	.word 0x00000194, 0x00000328
	.word 0x00000328, 0x000004BC
	.word 0x000004BC, 0x00000650
	.word 0x00000650, 0x000007E4
	.word 0x000007E4, 0x00000978
	.word 0x00000978, 0x00000B0C
	.word 0x00000B0C, 0x00000CA0

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000CA8 ; chunk size
	.incbin "baserom.nds", 0x1C21674, 0xCA0
	.balign 512, 255
