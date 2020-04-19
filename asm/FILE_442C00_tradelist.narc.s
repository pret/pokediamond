	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x442C00, 0x2A74
	.balign 512, 255
