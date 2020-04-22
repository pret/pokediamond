	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43FA00, 0x800
	.balign 512, 255
