	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C34C00, 0x6E0
	.balign 512, 255
