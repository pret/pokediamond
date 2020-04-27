	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x303400, 0x9100
	.balign 512, 255
