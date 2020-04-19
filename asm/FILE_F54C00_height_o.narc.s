	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0xF54C00, 0x694
	.balign 512, 255
