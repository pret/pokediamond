	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000DFE0 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000044 ; chunk size
	.short 7 ; number of files
	.balign 4
	.word 0x00000000, 0x0000C040
	.word 0x0000C040, 0x0000C480
	.word 0x0000C480, 0x0000C4E0
	.word 0x0000C4E0, 0x0000CD04
	.word 0x0000CD04, 0x0000D528
	.word 0x0000D528, 0x0000DD4C
	.word 0x0000DD4C, 0x0000DF74

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000DF7C ; chunk size
	.incbin "baserom.nds", 0x387EA6C, 0xC040
	.incbin "baserom.nds", 0x388AAAC, 0x440
	.incbin "baserom.nds", 0x388AEEC, 0x60
	.incbin "baserom.nds", 0x388AF4C, 0x824
	.incbin "baserom.nds", 0x388B770, 0x824
	.incbin "baserom.nds", 0x388BF94, 0x824
	.incbin "baserom.nds", 0x388C7B8, 0x228
