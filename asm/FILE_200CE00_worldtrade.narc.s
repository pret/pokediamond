	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x200CE00, 0xB6D8
	.balign 512, 255
