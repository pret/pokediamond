	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000085FC ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000003C ; chunk size
	.short 6 ; number of files
	.balign 4
	.word 0x00000000, 0x000002C8
	.word 0x000002C8, 0x0000078C
	.word 0x0000078C, 0x00001F6C
	.word 0x00001F6C, 0x000051D4
	.word 0x000051D4, 0x000070A8
	.word 0x000070A8, 0x00008598

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000085A0 ; chunk size
	.incbin "baserom.nds", 0x37A4464, 0x8598
	.balign 512, 255
