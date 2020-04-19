	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00004F04 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000002C ; chunk size
	.short 4 ; number of files
	.balign 4
	.word 0x00000000, 0x00002024
	.word 0x00002024, 0x00003048
	.word 0x00003048, 0x00004C88
	.word 0x00004C88, 0x00004EB0

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00004EB8 ; chunk size
	.incbin "baserom.nds", 0x0, 0x2024
	.incbin "baserom.nds", 0x2024, 0x1024
	.incbin "baserom.nds", 0x3048, 0x1C40
	.incbin "baserom.nds", 0x4C88, 0x228
	.balign 4, 255
