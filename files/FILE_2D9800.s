	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2D9800, 0x460
	.balign 512, 255
