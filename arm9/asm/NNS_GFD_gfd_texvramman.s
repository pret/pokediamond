	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	; NNS_GfdDefaultFuncAllocTexVram
	.global UNK_021064B8
UNK_021064B8: ; 0x021064B8
	.word FUN_020AE8B4

	; NNS_GfdDefaultFuncFreeTexVram
	.global UNK_021064BC
UNK_021064BC: ; 0x021064BC
	.word FUN_020AE8AC

	.section .text

	; _end
	arm_func_start FUN_020AE8AC
FUN_020AE8AC: ; 0x020AE8AC
	mvn r0, #0x0
	bx lr
	arm_func_end FUN_020AE8AC

	; _end
	arm_func_start FUN_020AE8B4
FUN_020AE8B4: ; 0x020AE8B4
	mov r0, #0x0
	bx lr
	arm_func_end FUN_020AE8B4

