	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x58FA00, 0x394C
	.balign 512, 255
