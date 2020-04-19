	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000010B8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000005C ; chunk size
	.short 10 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000450
	.word 0x00000450, 0x00000678
	.word 0x00000678, 0x000007B1
	.word 0x000007B4, 0x00000974
	.word 0x00000974, 0x00000AAD
	.word 0x00000AB0, 0x00000B8F
	.word 0x00000B90, 0x00000F0C
	.word 0x00000F0C, 0x00000FBC
	.word 0x00000FBC, 0x00001034

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000103C ; chunk size
	.incbin "baserom.nds", 0x0, 0x228
	.incbin "baserom.nds", 0x228, 0x228
	.incbin "baserom.nds", 0x450, 0x228
	.incbin "baserom.nds", 0x678, 0x139
	.incbin "baserom.nds", 0x7B4, 0x1C0
	.incbin "baserom.nds", 0x974, 0x139
	.incbin "baserom.nds", 0xAB0, 0xDF
	.incbin "baserom.nds", 0xB90, 0x37C
	.incbin "baserom.nds", 0xF0C, 0xB0
	.incbin "baserom.nds", 0xFBC, 0x78
	.balign 4, 255
