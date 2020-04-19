	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2528C00, 0x13504
	.balign 512, 255
