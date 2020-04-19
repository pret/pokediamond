	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DA6200, 0x19C74
	.balign 512, 255
