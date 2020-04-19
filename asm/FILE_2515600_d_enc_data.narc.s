	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2515600, 0x13504
	.balign 512, 255
