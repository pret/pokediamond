	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x184400, 0x32E0
	.balign 512, 255
