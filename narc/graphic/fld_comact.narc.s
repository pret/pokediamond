	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000364 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000002C ; chunk size
	.short 4 ; number of files
	.balign 4
	.word 0x00000000, 0x0000005A
	.word 0x0000005C, 0x0000018C
	.word 0x0000018C, 0x0000021A
	.word 0x0000021C, 0x0000030E

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000318 ; chunk size
	.incbin "baserom.nds", 0x0, 0x5A
	.incbin "baserom.nds", 0x5C, 0x130
	.incbin "baserom.nds", 0x18C, 0x8E
	.incbin "baserom.nds", 0x21C, 0xF2
	.balign 4, 255
