	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28F200, 0xCC0
	.balign 512, 255
