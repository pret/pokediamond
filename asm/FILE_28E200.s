	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28E200, 0x4C0
	.balign 512, 255
