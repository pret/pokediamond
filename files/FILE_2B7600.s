	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2B7600, 0x1C40
	.balign 512, 255
