	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x397AA00, 0xDB4C0
	.balign 512, 255
