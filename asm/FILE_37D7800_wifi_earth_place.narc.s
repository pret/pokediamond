	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x37D7800, 0xCC8
	.balign 512, 255
