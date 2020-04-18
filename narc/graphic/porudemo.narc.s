	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000226C ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000003C ; chunk size
	.short 6 ; number of files
	.balign 4
	.word 0x00000000, 0x0000005A
	.word 0x0000005C, 0x0000013E
	.word 0x00000140, 0x00000980
	.word 0x00000980, 0x000015C0
	.word 0x000015C0, 0x00001BE4
	.word 0x00001BE4, 0x00002208

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00002210 ; chunk size
	.incbin "baserom.nds", 0x1F87C64, 0x5A
	.incbin "baserom.nds", 0x1F87CC0, 0xE2
	.incbin "baserom.nds", 0x1F87DA4, 0x840
	.incbin "baserom.nds", 0x1F885E4, 0xC40
	.incbin "baserom.nds", 0x1F89224, 0x624
	.incbin "baserom.nds", 0x1F89848, 0x624
