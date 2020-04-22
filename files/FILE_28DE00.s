	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28DE00, 0x320
	.balign 512, 255
