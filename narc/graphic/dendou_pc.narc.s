	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000029C ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000024 ; chunk size
	.short 3 ; number of files
	.balign 4
	.word 0x00000000, 0x0000011B
	.word 0x0000011C, 0x000001D2
	.word 0x000001D4, 0x00000250

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000258 ; chunk size
	.incbin "baserom.nds", 0x0, 0x11B
	.incbin "baserom.nds", 0x11C, 0xB6
	.incbin "baserom.nds", 0x1D4, 0x7C
	.balign 4, 255
