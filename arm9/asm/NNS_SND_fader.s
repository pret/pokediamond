	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_SndFaderIsFinished
NNSi_SndFaderIsFinished: ; 0x020C3DDC
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0xc]
	cmp r1, r0
	movge r0, #0x1
	movlt r0, #0x0
	bx lr

	arm_func_start NNSi_SndFaderUpdate
NNSi_SndFaderUpdate: ; 0x020C3DF4
	ldr r2, [r0, #0x8]
	ldr r1, [r0, #0xc]
	cmp r2, r1
	addlt r1, r2, #0x1
	strlt r1, [r0, #0x8]
	bx lr

	arm_func_start NNSi_SndFaderGet
NNSi_SndFaderGet: ; 0x020C3E0C
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0xc]
	ldr r2, [r0, #0x8]
	cmp r2, r1
	ldrge r0, [r0, #0x4]
	ldmgeia sp!, {r4,pc}
	ldr r4, [r0, #0x0]
	ldr r0, [r0, #0x4]
	sub r0, r0, r4
	mul r0, r2, r0
	bl _s32_div_f
	add r0, r4, r0
	ldmia sp!, {r4,pc}

	arm_func_start NNSi_SndFaderSet
NNSi_SndFaderSet: ; 0x020C3E40
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl NNSi_SndFaderGet
	str r0, [r6, #0x0]
	str r5, [r6, #0x4]
	str r4, [r6, #0xc]
	mov r0, #0x0
	str r0, [r6, #0x8]
	ldmia sp!, {r4-r6,pc}

	arm_func_start NNSi_SndFaderInit
NNSi_SndFaderInit: ; 0x020C3E6C
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0xc]
	ldr r1, [r0, #0xc]
	str r1, [r0, #0x8]
	bx lr
