	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x44BA00, 0x694
	.balign 512, 255
