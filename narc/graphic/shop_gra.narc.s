	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00002740 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000064 ; chunk size
	.short 11 ; number of files
	.balign 4
	.word 0x00000000, 0x00000840
	.word 0x00000840, 0x00000A68
	.word 0x00000A68, 0x0000108C
	.word 0x0000108C, 0x000016B0
	.word 0x000016B0, 0x000017E0
	.word 0x000017E0, 0x0000186E
	.word 0x00001870, 0x00001972
	.word 0x00001974, 0x000023A4
	.word 0x000023A4, 0x0000241B
	.word 0x0000241C, 0x0000248B
	.word 0x0000248C, 0x000026B4

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000026BC ; chunk size
	.incbin "baserom.nds", 0x1FB028C, 0x840
	.incbin "baserom.nds", 0x1FB0ACC, 0x228
	.incbin "baserom.nds", 0x1FB0CF4, 0x624
	.incbin "baserom.nds", 0x1FB1318, 0x624
	.incbin "baserom.nds", 0x1FB193C, 0x130
	.incbin "baserom.nds", 0x1FB1A6C, 0x8E
	.incbin "baserom.nds", 0x1FB1AFC, 0x102
	.incbin "baserom.nds", 0x1FB1C00, 0xA30
	.incbin "baserom.nds", 0x1FB2630, 0x77
	.incbin "baserom.nds", 0x1FB26A8, 0x6F
	.incbin "baserom.nds", 0x1FB2718, 0x228
