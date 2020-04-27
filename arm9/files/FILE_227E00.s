	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x227E00, 0xF520
	.balign 512, 255
