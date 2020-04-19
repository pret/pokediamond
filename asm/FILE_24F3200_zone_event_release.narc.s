	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x24F3200, 0x222F4
	.balign 512, 255
