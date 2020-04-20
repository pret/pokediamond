	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2B9400, 0x3000
	.balign 512, 255
