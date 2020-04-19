	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00003868 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000044 ; chunk size
	.short 7 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000450
	.word 0x00000450, 0x00002890
	.word 0x00002890, 0x00002DC0
	.word 0x00002DC0, 0x000035E4
	.word 0x000035E4, 0x0000370E
	.word 0x00003710, 0x000037FA

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00003804 ; chunk size
	.incbin "baserom.nds", 0x0, 0x228
	.incbin "baserom.nds", 0x228, 0x228
	.incbin "baserom.nds", 0x450, 0x2440
	.incbin "baserom.nds", 0x2890, 0x530
	.incbin "baserom.nds", 0x2DC0, 0x824
	.incbin "baserom.nds", 0x35E4, 0x12A
	.incbin "baserom.nds", 0x3710, 0xEA
	.balign 4, 255
