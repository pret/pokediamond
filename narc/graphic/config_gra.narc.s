	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000002AC ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000024 ; chunk size
	.short 3 ; number of files
	.balign 4
	.word 0x00000000, 0x0000005A
	.word 0x0000005C, 0x0000013C
	.word 0x0000013C, 0x00000260

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000268 ; chunk size
	.incbin "baserom.nds", 0x1DDFE4C, 0x5A
	.incbin "baserom.nds", 0x1DDFEA8, 0xE0
	.incbin "baserom.nds", 0x1DDFF88, 0x124
