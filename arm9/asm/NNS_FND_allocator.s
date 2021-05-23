	.include "asm/macros.inc"
	.include "global.inc"

	.rodata

	.global UNK_020FF7CC
UNK_020FF7CC: ; 0x020FF7CC
	.word FUN_020AE894
	.word FUN_020AE884

	.text

	arm_func_start FUN_020AE82C
FUN_020AE82C: ; 0x020AE82C
	ldr ip, _020AE848 ; =UNK_020FF7CC
	mov r3, #0x0
	str r12, [r0, #0x0]
	str r1, [r0, #0x4]
	str r2, [r0, #0x8]
	str r3, [r0, #0xc]
	bx lr
	.balign 4
_020AE848: .word UNK_020FF7CC

	arm_func_start FUN_020AE84C
FUN_020AE84C: ; 0x020AE84C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	ldr r2, [r2, #0x4]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AE868
FUN_020AE868: ; 0x020AE868
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	ldr r2, [r2, #0x0]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AE884
FUN_020AE884: ; 0x020AE884
	ldr ip, _020AE890 ; =FUN_020ADDF0
	ldr r0, [r0, #0x4]
	bx r12
	.balign 4
_020AE890: .word FUN_020ADDF0

	arm_func_start FUN_020AE894
FUN_020AE894: ; 0x020AE894
	ldr ip, _020AE8A8 ; =tempName_NNS_FndAllocFromExpHeapEx
	mov r2, r0
	ldr r0, [r2, #0x4]
	ldr r2, [r2, #0x8]
	bx r12
	.balign 4
_020AE8A8: .word tempName_NNS_FndAllocFromExpHeapEx
