	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000014C8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000002C ; chunk size
	.short 4 ; number of files
	.balign 4
	.word 0x00000000, 0x0000009E
	.word 0x000000A0, 0x000012F0
	.word 0x000012F0, 0x000013E4
	.word 0x000013E4, 0x00001474

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000147C ; chunk size
	.incbin "baserom.nds", 0x1FA9254, 0x9E
	.incbin "baserom.nds", 0x1FA92F4, 0x1250
	.incbin "baserom.nds", 0x1FAA544, 0xF4
	.incbin "baserom.nds", 0x1FAA638, 0x90
