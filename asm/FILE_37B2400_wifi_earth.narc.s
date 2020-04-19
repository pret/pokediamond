	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x37B2400, 0x25274
	.balign 512, 255
