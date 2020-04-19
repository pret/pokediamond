	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000194 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000002C ; chunk size
	.short 4 ; number of files
	.balign 4
	.word 0x00000000, 0x00000050
	.word 0x00000050, 0x000000A0
	.word 0x000000A0, 0x000000F0
	.word 0x000000F0, 0x00000140

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000148 ; chunk size
	.incbin "baserom.nds", 0x0, 0x50
	.incbin "baserom.nds", 0x50, 0x50
	.incbin "baserom.nds", 0xA0, 0x50
	.incbin "baserom.nds", 0xF0, 0x50
	.balign 4, 255
