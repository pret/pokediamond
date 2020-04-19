	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3821C00, 0x25EC
	.balign 512, 255
