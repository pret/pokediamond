	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x441C00, 0x10C
	.balign 512, 255
