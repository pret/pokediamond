	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0xF55400, 0xD96EC
	.balign 512, 255
