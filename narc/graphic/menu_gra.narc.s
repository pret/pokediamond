	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00004B70 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000064 ; chunk size
	.short 11 ; number of files
	.balign 4
	.word 0x00000000, 0x0000006F
	.word 0x00000070, 0x000000E7
	.word 0x000000E8, 0x00000718
	.word 0x00000718, 0x000015D0
	.word 0x000015D0, 0x0000181C
	.word 0x0000181C, 0x00001A44
	.word 0x00001A44, 0x00002E74
	.word 0x00002E74, 0x000038D6
	.word 0x000038D8, 0x00003A8A
	.word 0x00003A8C, 0x00003CB4
	.word 0x00003CB4, 0x00004AE4

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00004AEC ; chunk size
	.incbin "baserom.nds", 0x1EF588C, 0x6F
	.incbin "baserom.nds", 0x1EF58FC, 0x77
	.incbin "baserom.nds", 0x1EF5974, 0x630
	.incbin "baserom.nds", 0x1EF5FA4, 0xEB8
	.incbin "baserom.nds", 0x1EF6E5C, 0x24C
	.incbin "baserom.nds", 0x1EF70A8, 0x228
	.incbin "baserom.nds", 0x1EF72D0, 0x1430
	.incbin "baserom.nds", 0x1EF8700, 0xA62
	.incbin "baserom.nds", 0x1EF9164, 0x1B2
	.incbin "baserom.nds", 0x1EF9318, 0x228
	.incbin "baserom.nds", 0x1EF9540, 0xE30
