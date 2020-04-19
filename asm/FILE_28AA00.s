	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28AA00, 0x1780
	.balign 512, 255
