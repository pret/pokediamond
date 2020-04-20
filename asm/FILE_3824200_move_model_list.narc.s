	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000264 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000008C ; chunk size
	.short 16 ; number of files
	.balign 4
	.word 0x00000000, 0x0000001C
	.word 0x0000001C, 0x00000038
	.word 0x00000038, 0x00000054
	.word 0x00000054, 0x00000070
	.word 0x00000070, 0x0000008C
	.word 0x0000008C, 0x000000A8
	.word 0x000000A8, 0x000000C4
	.word 0x000000C4, 0x000000E0
	.word 0x000000E0, 0x000000FC
	.word 0x000000FC, 0x00000118
	.word 0x00000118, 0x00000134
	.word 0x00000134, 0x00000150
	.word 0x00000150, 0x0000016C
	.word 0x0000016C, 0x00000188
	.word 0x00000188, 0x000001AC
	.word 0x000001AC, 0x000001B0

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000001B8 ; chunk size
	.incbin "baserom.nds", 0x38242B4, 0x1B0
	.balign 512, 255
