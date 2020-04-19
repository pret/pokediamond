	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E3A200, 0x22524
	.balign 512, 255
