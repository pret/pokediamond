	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00002F34 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000074 ; chunk size
	.short 13 ; number of files
	.balign 4
	.word 0x00000000, 0x0000006F
	.word 0x00000070, 0x000000EB
	.word 0x000000EC, 0x0000051C
	.word 0x0000051C, 0x0000063E
	.word 0x00000640, 0x000006CE
	.word 0x000006D0, 0x00000780
	.word 0x00000780, 0x000008A2
	.word 0x000008A4, 0x00000932
	.word 0x00000934, 0x000009E4
	.word 0x000009E4, 0x00000C0C
	.word 0x00000C0C, 0x00001C4C
	.word 0x00001C4C, 0x00002C70
	.word 0x00002C70, 0x00002E98

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00002EA0 ; chunk size
	.incbin "baserom.nds", 0x200149C, 0x6F
	.incbin "baserom.nds", 0x200150C, 0x7B
	.incbin "baserom.nds", 0x2001588, 0x430
	.incbin "baserom.nds", 0x20019B8, 0x122
	.incbin "baserom.nds", 0x2001ADC, 0x8E
	.incbin "baserom.nds", 0x2001B6C, 0xB0
	.incbin "baserom.nds", 0x2001C1C, 0x122
	.incbin "baserom.nds", 0x2001D40, 0x8E
	.incbin "baserom.nds", 0x2001DD0, 0xB0
	.incbin "baserom.nds", 0x2001E80, 0x228
	.incbin "baserom.nds", 0x20020A8, 0x1040
	.incbin "baserom.nds", 0x20030E8, 0x1024
	.incbin "baserom.nds", 0x200410C, 0x228
