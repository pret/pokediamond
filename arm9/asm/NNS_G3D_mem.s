	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; NNS_G3dFreeAnmObj
	arm_func_start thunk_FUN_020ae84c
thunk_FUN_020ae84c: ; 0x020BB8C4
	ldr ip, _020BB8CC ; =FUN_020AE84C
	bx r12
	.balign 4
_020BB8CC: .word FUN_020AE84C
	arm_func_end thunk_FUN_020ae84c

	; _end
	arm_func_start FUN_020BB8D0
FUN_020BB8D0: ; 0x020BB8D0
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, r1
	mov r1, r2
	bl FUN_020B81B0
	mov r1, r0
	mov r0, r4
	bl FUN_020AE868
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020BB8D0

