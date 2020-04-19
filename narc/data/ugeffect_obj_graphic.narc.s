	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00004D68 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000054 ; chunk size
	.short 9 ; number of files
	.balign 4
	.word 0x00000000, 0x00001230
	.word 0x00001230, 0x00001458
	.word 0x00001458, 0x00002688
	.word 0x00002688, 0x000028B0
	.word 0x000028B0, 0x000029A9
	.word 0x000029AC, 0x00002B15
	.word 0x00002B18, 0x00002BEE
	.word 0x00002BF0, 0x00002CBA
	.word 0x00002CBC, 0x00004CEC

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00004CF4 ; chunk size
	.incbin "baserom.nds", 0x0, 0x1230
	.incbin "baserom.nds", 0x1230, 0x228
	.incbin "baserom.nds", 0x1458, 0x1230
	.incbin "baserom.nds", 0x2688, 0x228
	.incbin "baserom.nds", 0x28B0, 0xF9
	.incbin "baserom.nds", 0x29AC, 0x169
	.incbin "baserom.nds", 0x2B18, 0xD6
	.incbin "baserom.nds", 0x2BF0, 0xCA
	.incbin "baserom.nds", 0x2CBC, 0x2030
	.balign 4, 255
