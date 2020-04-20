	.include "asm/macros.inc"
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
	.incbin "baserom.nds", 0x387EA6C, 0xDF74
	.balign 512, 255
