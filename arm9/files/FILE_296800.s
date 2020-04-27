	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x296800, 0xCA0
	.balign 512, 255
