	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00001A5C ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000008C ; chunk size
	.short 16 ; number of files
	.balign 4
	.word 0x00000000, 0x000008A0
	.word 0x000008A0, 0x00000A52
	.word 0x00000A54, 0x00000AB0
	.word 0x00000AB0, 0x00000D0C
	.word 0x00000D0C, 0x00000E14
	.word 0x00000E14, 0x00000EF6
	.word 0x00000EF8, 0x00000F86
	.word 0x00000F88, 0x00001016
	.word 0x00001018, 0x000010AE
	.word 0x000010B0, 0x00001148
	.word 0x00001148, 0x0000129C
	.word 0x0000129C, 0x00001326
	.word 0x00001328, 0x000013D8
	.word 0x000013D8, 0x00001408
	.word 0x00001408, 0x000014E4
	.word 0x000014E4, 0x000019A8

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000019B0 ; chunk size
	.incbin "baserom.nds", 0x0, 0x8A0
	.incbin "baserom.nds", 0x8A0, 0x1B2
	.incbin "baserom.nds", 0xA54, 0x5C
	.incbin "baserom.nds", 0xAB0, 0x25C
	.incbin "baserom.nds", 0xD0C, 0x108
	.incbin "baserom.nds", 0xE14, 0xE2
	.incbin "baserom.nds", 0xEF8, 0x8E
	.incbin "baserom.nds", 0xF88, 0x8E
	.incbin "baserom.nds", 0x1018, 0x96
	.incbin "baserom.nds", 0x10B0, 0x98
	.incbin "baserom.nds", 0x1148, 0x154
	.incbin "baserom.nds", 0x129C, 0x8A
	.incbin "baserom.nds", 0x1328, 0xB0
	.incbin "baserom.nds", 0x13D8, 0x30
	.incbin "baserom.nds", 0x1408, 0xDC
	.incbin "baserom.nds", 0x14E4, 0x4C4
	.balign 4, 255
