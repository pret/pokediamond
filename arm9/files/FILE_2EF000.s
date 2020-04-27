	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2EF000, 0x2540
	.balign 512, 255
