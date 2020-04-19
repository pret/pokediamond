	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DDBC00, 0x41F8
	.balign 512, 255
