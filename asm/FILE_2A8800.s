	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2A8800, 0x15A0
	.balign 512, 255
