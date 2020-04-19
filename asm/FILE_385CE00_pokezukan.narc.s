	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x385CE00, 0x418
	.balign 512, 255
