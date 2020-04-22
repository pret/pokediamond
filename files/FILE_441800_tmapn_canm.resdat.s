	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x441800, 0x94
	.balign 512, 255
