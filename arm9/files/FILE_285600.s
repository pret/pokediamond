	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x285600, 0x5C0
	.balign 512, 255
