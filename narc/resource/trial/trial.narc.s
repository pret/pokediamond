	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000DBE4 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000004C ; chunk size
	.short 8 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00006268
	.word 0x00006268, 0x00006A8C
	.word 0x00006A8C, 0x00006CB4
	.word 0x00006CB4, 0x0000CCF4
	.word 0x0000CCF4, 0x0000D518
	.word 0x0000D518, 0x0000D740
	.word 0x0000D740, 0x0000DB70

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000DB78 ; chunk size
	.incbin "baserom.nds", 0x395B074, 0x228
	.incbin "baserom.nds", 0x395B29C, 0x6040
	.incbin "baserom.nds", 0x39612DC, 0x824
	.incbin "baserom.nds", 0x3961B00, 0x228
	.incbin "baserom.nds", 0x3961D28, 0x6040
	.incbin "baserom.nds", 0x3967D68, 0x824
	.incbin "baserom.nds", 0x396858C, 0x228
	.incbin "baserom.nds", 0x39687B4, 0x430
