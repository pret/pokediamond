	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x442600, 0xBA
	.balign 512, 255
