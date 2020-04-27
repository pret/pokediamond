	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x288600, 0x9A0
	.balign 512, 255
