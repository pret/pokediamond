	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E5F200, 0xA8FC
	.balign 512, 255
