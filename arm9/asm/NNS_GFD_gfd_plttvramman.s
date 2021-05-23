	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	; NNS_GfdDefaultFuncAllocPlttVram
	.global UNK_021064C0
UNK_021064C0: ; 0x021064C0
	.word FUN_020AE8C4

	; NNS_GfdDefaultFuncFreePlttVram
	.global UNK_021064C4
UNK_021064C4: ; 0x021064C4
	.word FUN_020AE8BC

	.section .text

	; _end
	arm_func_start FUN_020AE8BC
FUN_020AE8BC: ; 0x020AE8BC
	mvn r0, #0x0
	bx lr
	arm_func_end FUN_020AE8BC

	; _end
	arm_func_start FUN_020AE8C4
FUN_020AE8C4: ; 0x020AE8C4
	mov r0, #0x0
	bx lr
	arm_func_end FUN_020AE8C4

