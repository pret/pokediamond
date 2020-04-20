	.include "asm/macros.inc"
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
	.incbin "baserom.nds", 0x1E73454, 0x310
	.balign 512, 255
