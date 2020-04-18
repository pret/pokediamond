	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000264 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000008C ; chunk size
	.short 16 ; number of files
	.balign 4
	.word 0x00000000, 0x0000001C
	.word 0x0000001C, 0x00000038
	.word 0x00000038, 0x00000054
	.word 0x00000054, 0x00000070
	.word 0x00000070, 0x0000008C
	.word 0x0000008C, 0x000000A8
	.word 0x000000A8, 0x000000C4
	.word 0x000000C4, 0x000000E0
	.word 0x000000E0, 0x000000FC
	.word 0x000000FC, 0x00000118
	.word 0x00000118, 0x00000134
	.word 0x00000134, 0x00000150
	.word 0x00000150, 0x0000016C
	.word 0x0000016C, 0x00000188
	.word 0x00000188, 0x000001AC
	.word 0x000001AC, 0x000001B0

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000001B8 ; chunk size
	.incbin "baserom.nds", 0x38242B4, 0x1C
	.incbin "baserom.nds", 0x38242D0, 0x1C
	.incbin "baserom.nds", 0x38242EC, 0x1C
	.incbin "baserom.nds", 0x3824308, 0x1C
	.incbin "baserom.nds", 0x3824324, 0x1C
	.incbin "baserom.nds", 0x3824340, 0x1C
	.incbin "baserom.nds", 0x382435C, 0x1C
	.incbin "baserom.nds", 0x3824378, 0x1C
	.incbin "baserom.nds", 0x3824394, 0x1C
	.incbin "baserom.nds", 0x38243B0, 0x1C
	.incbin "baserom.nds", 0x38243CC, 0x1C
	.incbin "baserom.nds", 0x38243E8, 0x1C
	.incbin "baserom.nds", 0x3824404, 0x1C
	.incbin "baserom.nds", 0x3824420, 0x1C
	.incbin "baserom.nds", 0x382443C, 0x24
	.incbin "baserom.nds", 0x3824460, 0x4
