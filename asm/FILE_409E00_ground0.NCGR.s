	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x409E00, 0x8030
	.balign 512, 255
