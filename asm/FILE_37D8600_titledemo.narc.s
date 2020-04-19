	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x37D8600, 0x37B10
	.balign 512, 255
