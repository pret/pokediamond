	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00006BBC ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000B4 ; chunk size
	.short 21 ; number of files
	.balign 4
	.word 0x00000000, 0x00000424
	.word 0x00000424, 0x00000848
	.word 0x00000848, 0x00001088
	.word 0x00001088, 0x000016AC
	.word 0x000016AC, 0x00001CD0
	.word 0x00001CD0, 0x00001EF8
	.word 0x00001EF8, 0x00002120
	.word 0x00002120, 0x000021BA
	.word 0x000021BC, 0x0000225E
	.word 0x00002260, 0x00002488
	.word 0x00002488, 0x000024F7
	.word 0x000024F8, 0x00002577
	.word 0x00002578, 0x000027A0
	.word 0x000027A0, 0x000043E0
	.word 0x000043E0, 0x00004608
	.word 0x00004608, 0x00004C2C
	.word 0x00004C2C, 0x00005250
	.word 0x00005250, 0x00005874
	.word 0x00005874, 0x00005E98
	.word 0x00005E98, 0x000064BC
	.word 0x000064BC, 0x00006AE0

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00006AE8 ; chunk size
	.incbin "baserom.nds", 0x0, 0x424
	.incbin "baserom.nds", 0x424, 0x424
	.incbin "baserom.nds", 0x848, 0x840
	.incbin "baserom.nds", 0x1088, 0x624
	.incbin "baserom.nds", 0x16AC, 0x624
	.incbin "baserom.nds", 0x1CD0, 0x228
	.incbin "baserom.nds", 0x1EF8, 0x228
	.incbin "baserom.nds", 0x2120, 0x9A
	.incbin "baserom.nds", 0x21BC, 0xA2
	.incbin "baserom.nds", 0x2260, 0x228
	.incbin "baserom.nds", 0x2488, 0x6F
	.incbin "baserom.nds", 0x24F8, 0x7F
	.incbin "baserom.nds", 0x2578, 0x228
	.incbin "baserom.nds", 0x27A0, 0x1C40
	.incbin "baserom.nds", 0x43E0, 0x228
	.incbin "baserom.nds", 0x4608, 0x624
	.incbin "baserom.nds", 0x4C2C, 0x624
	.incbin "baserom.nds", 0x5250, 0x624
	.incbin "baserom.nds", 0x5874, 0x624
	.incbin "baserom.nds", 0x5E98, 0x624
	.incbin "baserom.nds", 0x64BC, 0x624
	.balign 4, 255
