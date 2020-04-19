	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x210B600, 0xE4EC
	.balign 512, 255
