	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00007B18 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000EC ; chunk size
	.short 28 ; number of files
	.balign 4
	.word 0x00000000, 0x0000080E
	.word 0x00000810, 0x0000101E
	.word 0x00001020, 0x00001217
	.word 0x00001218, 0x00001452
	.word 0x00001454, 0x00001D78
	.word 0x00001D78, 0x0000274B
	.word 0x0000274C, 0x00002986
	.word 0x00002988, 0x00002AE3
	.word 0x00002AE4, 0x00002BC1
	.word 0x00002BC4, 0x000031E1
	.word 0x000031E4, 0x00003260
	.word 0x00003260, 0x000032E0
	.word 0x000032E0, 0x0000334A
	.word 0x0000334C, 0x000033AA
	.word 0x000033AC, 0x00003406
	.word 0x00003408, 0x00003ABD
	.word 0x00003AC0, 0x00004AD3
	.word 0x00004AD4, 0x00004B94
	.word 0x00004B94, 0x00004C85
	.word 0x00004C88, 0x00004D12
	.word 0x00004D14, 0x00004D6E
	.word 0x00004D70, 0x00004E4F
	.word 0x00004E50, 0x00004E93
	.word 0x00004E94, 0x00004EEE
	.word 0x00004EF0, 0x000053B6
	.word 0x000053B8, 0x000057ED
	.word 0x000057F0, 0x0000584A
	.word 0x0000584C, 0x00007A04

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00007A0C ; chunk size
	.incbin "baserom.nds", 0x1DE0314, 0x7A04
	.balign 512, 255
