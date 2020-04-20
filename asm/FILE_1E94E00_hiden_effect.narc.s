	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00007E14 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000084 ; chunk size
	.short 15 ; number of files
	.balign 4
	.word 0x00000000, 0x00001284
	.word 0x00001284, 0x0000148C
	.word 0x0000148C, 0x000017E8
	.word 0x000017E8, 0x00002880
	.word 0x00002880, 0x00004180
	.word 0x00004180, 0x00004330
	.word 0x00004330, 0x00004404
	.word 0x00004404, 0x00004760
	.word 0x00004760, 0x000054F0
	.word 0x000054F0, 0x000056A4
	.word 0x000056A4, 0x000057D4
	.word 0x000057D4, 0x000068B0
	.word 0x000068B0, 0x00006B64
	.word 0x00006B64, 0x00006C8C
	.word 0x00006C8C, 0x00007D68

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00007D70 ; chunk size
	.incbin "baserom.nds", 0x1E94EAC, 0x7D68
	.balign 512, 255
