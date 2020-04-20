	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00003E14 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000064 ; chunk size
	.short 11 ; number of files
	.balign 4
	.word 0x00000000, 0x0000013A
	.word 0x0000013C, 0x00000236
	.word 0x00000238, 0x00000DB8
	.word 0x00000DB8, 0x00000FE0
	.word 0x00000FE0, 0x00001604
	.word 0x00001604, 0x00001C28
	.word 0x00001C28, 0x0000224C
	.word 0x0000224C, 0x000024FC
	.word 0x000024FC, 0x00002724
	.word 0x00002724, 0x00003764
	.word 0x00003764, 0x00003D88

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00003D90 ; chunk size
	.incbin "baserom.nds", 0x59348C, 0x3D88
	.balign 512, 255
