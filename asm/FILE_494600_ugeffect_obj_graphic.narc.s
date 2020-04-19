	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x494600, 0x4D68
	.balign 512, 255
