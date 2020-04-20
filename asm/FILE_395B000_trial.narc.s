	.include "asm/macros.inc"
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
	.incbin "baserom.nds", 0x395B074, 0xDB70
	.balign 512, 255
