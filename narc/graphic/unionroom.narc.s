	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00001210 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000004C ; chunk size
	.short 8 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000450
	.word 0x00000450, 0x00000859
	.word 0x0000085C, 0x00000BB2
	.word 0x00000BB4, 0x00000CD7
	.word 0x00000CD8, 0x00001006
	.word 0x00001008, 0x000010C4
	.word 0x000010C4, 0x0000119B

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000011A4 ; chunk size
	.incbin "baserom.nds", 0x2000074, 0x228
	.incbin "baserom.nds", 0x200029C, 0x228
	.incbin "baserom.nds", 0x20004C4, 0x409
	.incbin "baserom.nds", 0x20008D0, 0x356
	.incbin "baserom.nds", 0x2000C28, 0x123
	.incbin "baserom.nds", 0x2000D4C, 0x32E
	.incbin "baserom.nds", 0x200107C, 0xBC
	.incbin "baserom.nds", 0x2001138, 0xD7
