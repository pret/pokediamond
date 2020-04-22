	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x145400, 0x261A0
	.balign 512, 255
