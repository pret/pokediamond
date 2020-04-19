	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00003F58 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000A4 ; chunk size
	.short 19 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000450
	.word 0x00000450, 0x00000B29
	.word 0x00000B2C, 0x00000D83
	.word 0x00000D84, 0x00000EA2
	.word 0x00000EA4, 0x00000FE1
	.word 0x00000FE4, 0x000010B3
	.word 0x000010B4, 0x00001184
	.word 0x00001184, 0x00001254
	.word 0x00001254, 0x00001324
	.word 0x00001324, 0x00002D15
	.word 0x00002D18, 0x00002F9A
	.word 0x00002F9C, 0x00003401
	.word 0x00003404, 0x0000354B
	.word 0x0000354C, 0x00003A74
	.word 0x00003A74, 0x00003B13
	.word 0x00003B14, 0x00003C1F
	.word 0x00003C20, 0x00003D4F
	.word 0x00003D50, 0x00003E8A

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00003E94 ; chunk size
	.incbin "baserom.nds", 0x0, 0x228
	.incbin "baserom.nds", 0x228, 0x228
	.incbin "baserom.nds", 0x450, 0x6D9
	.incbin "baserom.nds", 0xB2C, 0x257
	.incbin "baserom.nds", 0xD84, 0x11E
	.incbin "baserom.nds", 0xEA4, 0x13D
	.incbin "baserom.nds", 0xFE4, 0xCF
	.incbin "baserom.nds", 0x10B4, 0xD0
	.incbin "baserom.nds", 0x1184, 0xD0
	.incbin "baserom.nds", 0x1254, 0xD0
	.incbin "baserom.nds", 0x1324, 0x19F1
	.incbin "baserom.nds", 0x2D18, 0x282
	.incbin "baserom.nds", 0x2F9C, 0x465
	.incbin "baserom.nds", 0x3404, 0x147
	.incbin "baserom.nds", 0x354C, 0x528
	.incbin "baserom.nds", 0x3A74, 0x9F
	.incbin "baserom.nds", 0x3B14, 0x10B
	.incbin "baserom.nds", 0x3C20, 0x12F
	.incbin "baserom.nds", 0x3D50, 0x13A
	.balign 4, 255
