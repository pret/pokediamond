	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1FC8400, 0x37BE0
	.balign 512, 255
