	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3938000, 0x117E0
	.balign 512, 255
