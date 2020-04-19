	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x445C00, 0x5C80
	.balign 512, 255
