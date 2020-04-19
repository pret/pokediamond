	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x289600, 0x800
	.balign 512, 255
