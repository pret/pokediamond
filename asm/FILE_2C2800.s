	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2C2800, 0x23A0
	.balign 512, 255
