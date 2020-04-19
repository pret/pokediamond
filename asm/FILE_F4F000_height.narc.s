	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0xF4F000, 0x5A44
	.balign 512, 255
