	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x292E00, 0x1140
	.balign 512, 255
