	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2710800, 0x1724
	.balign 512, 255
