	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x296EC00, 0x4D8
	.balign 512, 255
