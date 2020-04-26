	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x30C600, 0x820
	.balign 512, 255
