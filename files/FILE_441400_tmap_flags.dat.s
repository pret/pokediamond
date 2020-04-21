	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x441400, 0x2DC
	.balign 512, 255
