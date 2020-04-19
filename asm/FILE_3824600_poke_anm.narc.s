	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3824600, 0x6344
	.balign 512, 255
