	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x385AA00, 0x22F0
	.balign 512, 255
