	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F03000, 0x2CE70
	.balign 512, 255
