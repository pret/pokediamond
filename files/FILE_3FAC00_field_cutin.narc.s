	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000D220 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000A4 ; chunk size
	.short 19 ; number of files
	.balign 4
	.word 0x00000000, 0x00008040
	.word 0x00008040, 0x00008864
	.word 0x00008864, 0x00008A8C
	.word 0x00008A8C, 0x00008CB4
	.word 0x00008CB4, 0x00008EDC
	.word 0x00008EDC, 0x00009B8C
	.word 0x00009B8C, 0x00009C0B
	.word 0x00009C0C, 0x0000A03C
	.word 0x0000A03C, 0x0000A09F
	.word 0x0000A0A0, 0x0000A10F
	.word 0x0000A110, 0x0000A240
	.word 0x0000A240, 0x0000A2BE
	.word 0x0000A2C0, 0x0000A35A
	.word 0x0000A35C, 0x0000B78C
	.word 0x0000B78C, 0x0000B8C5
	.word 0x0000B8C8, 0x0000BA55
	.word 0x0000BA58, 0x0000CE88
	.word 0x0000CE88, 0x0000CFC1
	.word 0x0000CFC4, 0x0000D151

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000D15C ; chunk size
	.incbin "baserom.nds", 0x3FACCC, 0xD154
	.balign 512, 255
