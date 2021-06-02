	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global NNS_GfdDefaultFuncAllocPlttVram
NNS_GfdDefaultFuncAllocPlttVram: ; 0x021064C0
	.word AllocPlttVram_

	.global NNS_GfdDefaultFuncFreePlttVram
NNS_GfdDefaultFuncFreePlttVram: ; 0x021064C4
	.word FreePlttVram_

	.section .text

	arm_func_start FreePlttVram_
FreePlttVram_: ; 0x020AE8BC
	mvn r0, #0x0
	bx lr
	arm_func_end FreePlttVram_

	arm_func_start AllocPlttVram_
AllocPlttVram_: ; 0x020AE8C4
	mov r0, #0x0
	bx lr
	arm_func_end AllocPlttVram_
