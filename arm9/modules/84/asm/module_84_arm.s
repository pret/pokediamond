	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD84_021D80B8
MOD84_021D80B8: ; 0x021D80B8
	stmdb sp!, {r3, r4, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	lr, r1
	mov	ip, r2
	str	r3, [sp]
	ldr	r0, _021D80EC ; =0x04000050
	mov	r1, r4
	mov	r2, lr
	mov	r3, ip
	bl	G2x_SetBlendAlpha_
	add	sp, sp, #4
	ldmia sp!, {r3, r4, pc}
_021D80EC: .word 0x04000050
	arm_func_end MOD84_021D80B8

	arm_func_start MOD84_021D80F0
MOD84_021D80F0: ; 0x021D80F0
	ldr	r2, _021D8100 ; =0x04000052
	orr	r0, r0, r1, lsl #8
	strh	r0, [r2]
	bx	lr
_021D8100: .word 0x04000052
	arm_func_end MOD84_021D80F0

	arm_func_start MOD84_021D8104
MOD84_021D8104: ; 0x021D8104
	stmdb sp!, {r3, r4, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	lr, r1
	mov	ip, r2
	str	r3, [sp]
	ldr	r0, _021D8138 ; =0x04001050
	mov	r1, r4
	mov	r2, lr
	mov	r3, ip
	bl	G2x_SetBlendAlpha_
	add	sp, sp, #4
	ldmia sp!, {r3, r4, pc}
_021D8138: .word 0x04001050
	arm_func_end MOD84_021D8104

	arm_func_start MOD84_021D813C
MOD84_021D813C: ; 0x021D813C
	ldr	r2, _021D814C ; =0x04001052
	orr	r0, r0, r1, lsl #8
	strh	r0, [r2]
	bx	lr
_021D814C: .word 0x04001052
	arm_func_end MOD84_021D813C
