	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000041F8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000054 ; chunk size
	.short 9 ; number of files
	.balign 4
	.word 0x00000000, 0x0000007C
	.word 0x0000007C, 0x000013AC
	.word 0x000013AC, 0x000014EA
	.word 0x000014EC, 0x0000162E
	.word 0x00001630, 0x000016CE
	.word 0x000016D0, 0x00002F10
	.word 0x00002F10, 0x00003534
	.word 0x00003534, 0x00003B58
	.word 0x00003B58, 0x0000417C

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00004184 ; chunk size
	.incbin "baserom.nds", 0x0, 0x7C
	.incbin "baserom.nds", 0x7C, 0x1330
	.incbin "baserom.nds", 0x13AC, 0x13E
	.incbin "baserom.nds", 0x14EC, 0x142
	.incbin "baserom.nds", 0x1630, 0x9E
	.incbin "baserom.nds", 0x16D0, 0x1840
	.incbin "baserom.nds", 0x2F10, 0x624
	.incbin "baserom.nds", 0x3534, 0x624
	.incbin "baserom.nds", 0x3B58, 0x624
	.balign 4, 255
