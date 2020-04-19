	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3861000, 0x2494
	.balign 512, 255
