/* rom1.5.s TODO: Disassemble */
	.include "asm/macros.inc"
	.section .text

	arm_func_start FUN_020AF030
FUN_020AF030:
	.incbin "baserom.nds", 0xB3030, 0x1ABDC


; _020AF02C = 0xB302C
; should end on 0xCDC0C = 020C9C0C
