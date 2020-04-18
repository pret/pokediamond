	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000061C ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000034 ; chunk size
	.short 5 ; number of files
	.balign 4
	.word 0x00000000, 0x0000013D
	.word 0x00000140, 0x00000284
	.word 0x00000284, 0x0000039F
	.word 0x000003A0, 0x0000051D
	.word 0x00000520, 0x000005BE

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000005C8 ; chunk size
	.incbin "baserom.nds", 0x1DE7E5C, 0x13D
	.incbin "baserom.nds", 0x1DE7F9C, 0x144
	.incbin "baserom.nds", 0x1DE80E0, 0x11B
	.incbin "baserom.nds", 0x1DE81FC, 0x17D
	.incbin "baserom.nds", 0x1DE837C, 0x9E
