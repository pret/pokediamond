	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000025EC ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000001C ; chunk size
	.short 2 ; number of files
	.balign 4
	.word 0x00000000, 0x000014CC
	.word 0x000014CC, 0x000025A8

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000025B0 ; chunk size
	.incbin "baserom.nds", 0x3821C44, 0x25A8
	.balign 512, 255
