	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x207E400, 0x8D0F0
	.balign 512, 255
