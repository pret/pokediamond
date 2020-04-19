	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x285C00, 0xF00
	.balign 512, 255
