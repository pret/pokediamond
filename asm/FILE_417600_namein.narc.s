	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00003F58 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000A4 ; chunk size
	.short 19 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000450
	.word 0x00000450, 0x00000B29
	.word 0x00000B2C, 0x00000D83
	.word 0x00000D84, 0x00000EA2
	.word 0x00000EA4, 0x00000FE1
	.word 0x00000FE4, 0x000010B3
	.word 0x000010B4, 0x00001184
	.word 0x00001184, 0x00001254
	.word 0x00001254, 0x00001324
	.word 0x00001324, 0x00002D15
	.word 0x00002D18, 0x00002F9A
	.word 0x00002F9C, 0x00003401
	.word 0x00003404, 0x0000354B
	.word 0x0000354C, 0x00003A74
	.word 0x00003A74, 0x00003B13
	.word 0x00003B14, 0x00003C1F
	.word 0x00003C20, 0x00003D4F
	.word 0x00003D50, 0x00003E8A

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00003E94 ; chunk size
	.incbin "baserom.nds", 0x4176CC, 0x3E8C
	.balign 512, 255
