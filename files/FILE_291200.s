	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x291200, 0xCC0
	.balign 512, 255
