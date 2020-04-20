	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x597C00, 0x723560
	.balign 512, 255
