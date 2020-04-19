	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2A6200, 0x2540
	.balign 512, 255
