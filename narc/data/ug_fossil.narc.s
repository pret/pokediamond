	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00003ED8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000024 ; chunk size
	.short 3 ; number of files
	.balign 4
	.word 0x00000000, 0x00003640
	.word 0x00003640, 0x00003868
	.word 0x00003868, 0x00003E8C

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00003E94 ; chunk size
	.incbin "baserom.nds", 0x0, 0x3640
	.incbin "baserom.nds", 0x3640, 0x228
	.incbin "baserom.nds", 0x3868, 0x624
	.balign 4, 255
