	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020B1A40
FUN_020B1A40: ; 0x020B1A40
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r1, r4, #0x4
	mov r0, #0x0
	mov r2, #0x18
	bl MIi_CpuClear16
	mov r0, #0x1000
	str r0, [r4, #0x4]
	str r0, [r4, #0x8]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B1A40

	; NNSi_G2dSrtcInitControl
	arm_func_start FUN_020B1A68
FUN_020B1A68: ; 0x020B1A68
	ldr ip, _020B1A74 ; =FUN_020B1A40
	str r1, [r0, #0x0]
	bx r12
	.balign 4
_020B1A74: .word FUN_020B1A40
	arm_func_end FUN_020B1A68

	; _end
	arm_func_start FUN_020B1A78
FUN_020B1A78: ; 0x020B1A78
	ldr r3, [r0, #0x0]
	cmp r3, #0x1
	ldreqh r3, [r0, #0x12]
	orreq r3, r3, #0x2
	streqh r3, [r0, #0x12]
	streq r1, [r0, #0x4]
	streq r2, [r0, #0x8]
	bx lr
	arm_func_end FUN_020B1A78

	; _end
	arm_func_start FUN_020B1A98
FUN_020B1A98: ; 0x020B1A98
	ldr r2, [r0, #0x0]
	cmp r2, #0x1
	ldreqh r2, [r0, #0x12]
	orreq r2, r2, #0x4
	streqh r2, [r0, #0x12]
	streqh r1, [r0, #0x10]
	bx lr
	arm_func_end FUN_020B1A98

	; _end
	arm_func_start FUN_020B1AB4
FUN_020B1AB4: ; 0x020B1AB4
	ldr r3, [r0, #0x0]
	cmp r3, #0x1
	ldreqh r3, [r0, #0x12]
	orreq r3, r3, #0x8
	streqh r3, [r0, #0x12]
	streqh r1, [r0, #0xc]
	streqh r2, [r0, #0xe]
	bx lr
	arm_func_end FUN_020B1AB4

