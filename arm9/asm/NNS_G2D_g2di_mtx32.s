	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G2dMtxConcat32
NNSi_G2dMtxConcat32: ; 0x020B423C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x1c
	ldr r4, [r0, #0x4]
	ldr r3, [r1, #0x8]
	mov r12, r2
	smull r6, r5, r4, r3
	ldr r4, [r0, #0x0]
	ldr r3, [r1, #0x0]
	cmp r12, r1
	smlal r6, r5, r4, r3
	mov r3, r6, lsr #0xc
	addeq r2, sp, #0x0
	orr r3, r3, r5, lsl #0x14
	str r3, [r2, #0x0]
	ldr r4, [r0, #0x4]
	ldr r3, [r1, #0xc]
	ldr r5, [r0, #0x0]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x4]
	add lr, sp, #0x0
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0x4]
	ldr r4, [r0, #0xc]
	ldr r3, [r1, #0x8]
	ldr r5, [r0, #0x8]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x0]
	cmp r2, lr
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0x8]
	ldr r4, [r0, #0xc]
	ldr r3, [r1, #0xc]
	ldr r5, [r0, #0x8]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x4]
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0xc]
	ldr r4, [r0, #0x14]
	ldr r3, [r1, #0x8]
	ldr r5, [r0, #0x10]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x0]
	ldr r4, [r1, #0x10]
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	add r3, r4, r3
	str r3, [r2, #0x10]
	ldr r4, [r0, #0x14]
	ldr r3, [r1, #0xc]
	ldr r5, [r0, #0x10]
	ldr r0, [r1, #0x4]
	smull r6, r3, r4, r3
	smlal r6, r3, r5, r0
	mov r0, r6, lsr #0xc
	ldr r1, [r1, #0x14]
	orr r0, r0, r3, lsl #0x14
	add r0, r1, r0
	str r0, [r2, #0x14]
	ldmeqia lr!, {r0-r3}
	stmeqia r12!, {r0-r3}
	ldmeqia lr, {r0-r1}
	stmeqia r12, {r0-r1}
	add sp, sp, #0x1c
	ldmia sp!, {r4-r7,pc}
	arm_func_end NNSi_G2dMtxConcat32
