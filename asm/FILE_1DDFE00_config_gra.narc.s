	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DDFE00, 0x2AC
	.balign 512, 255
