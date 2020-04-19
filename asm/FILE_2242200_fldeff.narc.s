	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2242200, 0x1BE98
	.balign 512, 255
