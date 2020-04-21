	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00002494 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000001C ; chunk size
	.short 2 ; number of files
	.balign 4
	.word 0x00000000, 0x0000227C
	.word 0x0000227C, 0x00002450

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00002458 ; chunk size
	.incbin "baserom.nds", 0x3861044, 0x2450
	.balign 512, 255
