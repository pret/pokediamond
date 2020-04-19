	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x37A0C00, 0x373C
	.balign 512, 255
