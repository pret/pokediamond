	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3923C00, 0x64C4
	.balign 512, 255
