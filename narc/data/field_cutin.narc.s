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
	.incbin "baserom.nds", 0x0, 0x8040
	.incbin "baserom.nds", 0x8040, 0x824
	.incbin "baserom.nds", 0x8864, 0x228
	.incbin "baserom.nds", 0x8A8C, 0x228
	.incbin "baserom.nds", 0x8CB4, 0x228
	.incbin "baserom.nds", 0x8EDC, 0xCB0
	.incbin "baserom.nds", 0x9B8C, 0x7F
	.incbin "baserom.nds", 0x9C0C, 0x430
	.incbin "baserom.nds", 0xA03C, 0x63
	.incbin "baserom.nds", 0xA0A0, 0x6F
	.incbin "baserom.nds", 0xA110, 0x130
	.incbin "baserom.nds", 0xA240, 0x7E
	.incbin "baserom.nds", 0xA2C0, 0x9A
	.incbin "baserom.nds", 0xA35C, 0x1430
	.incbin "baserom.nds", 0xB78C, 0x139
	.incbin "baserom.nds", 0xB8C8, 0x18D
	.incbin "baserom.nds", 0xBA58, 0x1430
	.incbin "baserom.nds", 0xCE88, 0x139
	.incbin "baserom.nds", 0xCFC4, 0x18D
	.balign 4, 255
