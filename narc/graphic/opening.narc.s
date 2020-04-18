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
	.incbin "baserom.nds", 0x1F5DADC, 0x424
	.incbin "baserom.nds", 0x1F5DF00, 0x424
	.incbin "baserom.nds", 0x1F5E324, 0x840
	.incbin "baserom.nds", 0x1F5EB64, 0x624
	.incbin "baserom.nds", 0x1F5F188, 0x624
	.incbin "baserom.nds", 0x1F5F7AC, 0x228
	.incbin "baserom.nds", 0x1F5F9D4, 0x228
	.incbin "baserom.nds", 0x1F5FBFC, 0x9A
	.incbin "baserom.nds", 0x1F5FC98, 0xA2
	.incbin "baserom.nds", 0x1F5FD3C, 0x228
	.incbin "baserom.nds", 0x1F5FF64, 0x6F
	.incbin "baserom.nds", 0x1F5FFD4, 0x7F
	.incbin "baserom.nds", 0x1F60054, 0x228
	.incbin "baserom.nds", 0x1F6027C, 0x1C40
	.incbin "baserom.nds", 0x1F61EBC, 0x228
	.incbin "baserom.nds", 0x1F620E4, 0x624
	.incbin "baserom.nds", 0x1F62708, 0x624
	.incbin "baserom.nds", 0x1F62D2C, 0x624
	.incbin "baserom.nds", 0x1F63350, 0x624
	.incbin "baserom.nds", 0x1F63974, 0x624
	.incbin "baserom.nds", 0x1F63F98, 0x624
