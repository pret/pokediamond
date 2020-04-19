	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x442A00, 0x95
	.balign 512, 255
