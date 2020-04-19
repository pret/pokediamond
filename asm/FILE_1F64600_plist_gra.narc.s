	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F64600, 0x9CAC
	.balign 512, 255
