	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2FFA00, 0x3920
	.balign 512, 255
