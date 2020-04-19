	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000BC8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000001C ; chunk size
	.short 2 ; number of files
	.balign 4
	.word 0x00000000, 0x0000029C
	.word 0x0000029C, 0x00000B84

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000B8C ; chunk size
	.incbin "baserom.nds", 0x0, 0x29C
	.incbin "baserom.nds", 0x29C, 0x8E8
	.balign 4, 255
