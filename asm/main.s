/* main.s TODO: Disassemble */
	.include "asm/macros.inc"

	.section .text

	thumb_func_start NitroMain
NitroMain:
	.incbin "baserom.nds", 0x4C54, 0x1A0
	thumb_func_end NitroMain
