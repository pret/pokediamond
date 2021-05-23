	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global NNS_GfdDefaultFuncAllocTexVram
NNS_GfdDefaultFuncAllocTexVram: ; 0x021064B8
	.word AllocTexVram_

	.global NNS_GfdDefaultFuncFreeTexVram
NNS_GfdDefaultFuncFreeTexVram: ; 0x021064BC
	.word FreeTexVram_

	.section .text

	arm_func_start FreeTexVram_
FreeTexVram_: ; 0x020AE8AC
	mvn r0, #0x0
	bx lr
	arm_func_end FreeTexVram_

	arm_func_start AllocTexVram_
AllocTexVram_: ; 0x020AE8B4
	mov r0, #0x0
	bx lr
	arm_func_end AllocTexVram_
