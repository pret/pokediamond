	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000380 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000024 ; chunk size
	.short 3 ; number of files
	.balign 4
	.word 0x00000000, 0x000002A0
	.word 0x000002A0, 0x000002E8
	.word 0x000002E8, 0x00000334

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000033C ; chunk size
	.incbin "baserom.nds", 0x385A64C, 0x334
	.balign 512, 255
