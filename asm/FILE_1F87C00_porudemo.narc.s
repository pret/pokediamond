	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F87C00, 0x226C
	.balign 512, 255
