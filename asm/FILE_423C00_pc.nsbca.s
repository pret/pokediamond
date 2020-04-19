	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x423C00, 0x18C
	.balign 512, 255
