	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_GfdFreeLnkVram
NNSi_GfdFreeLnkVram: ; 0x020AF334
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x10
	add r3, r2, r3
	str r2, [sp, #0x0]
	str r2, [sp, #0x8]
	str r3, [sp, #0x4]
	str r3, [sp, #0xc]
	ldr r3, [r0, #0x0]
	add r12, sp, #0x0
	cmp r3, #0x0
	beq _020AF418
	mov r6, #0x0
_020AF364:
	ldr r5, [r3, #0x0]
	ldr r4, [r12, #0x4]
	ldr r2, [r3, #0xc]
	cmp r5, r4
	bne _020AF3B8
	ldr r4, [r3, #0x4]
	add r4, r5, r4
	str r4, [sp, #0xc]
	ldr r4, [r3, #0x8]
	cmp r4, #0x0
	strne r2, [r4, #0xc]
	streq r2, [r0, #0x0]
	cmp r2, #0x0
	strne r4, [r2, #0x8]
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	strne r3, [r4, #0x8]
	ldr r4, [r1, #0x0]
	str r4, [r3, #0xc]
	str r6, [r3, #0x8]
	str r3, [r1, #0x0]
_020AF3B8:
	ldr r5, [r3, #0x0]
	ldr lr, [r3, #0x4]
	ldr r4, [r12, #0x0]
	add lr, r5, lr
	cmp r4, lr
	bne _020AF40C
	str r5, [sp, #0x8]
	ldr r5, [r3, #0x8]
	ldr r4, [r3, #0xc]
	cmp r5, #0x0
	strne r4, [r5, #0xc]
	streq r4, [r0, #0x0]
	cmp r4, #0x0
	strne r5, [r4, #0x8]
	ldr lr, [r1, #0x0]
	cmp lr, #0x0
	strne r3, [lr, #0x8]
	ldr lr, [r1, #0x0]
	str lr, [r3, #0xc]
	str r6, [r3, #0x8]
	str r3, [r1, #0x0]
_020AF40C:
	mov r3, r2
	cmp r2, #0x0
	bne _020AF364
_020AF418:
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	ldrne r2, [r4, #0xc]
	strne r2, [r1, #0x0]
	cmp r4, #0x0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, [sp, #0x8]
	mov r1, #0x0
	str r2, [r4, #0x0]
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x8]
	sub r2, r3, r2
	str r2, [r4, #0x4]
	str r1, [r4, #0x8]
	str r1, [r4, #0xc]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	strne r4, [r1, #0x8]
	ldr r2, [r0, #0x0]
	mov r1, #0x0
	str r2, [r4, #0xc]
	str r1, [r4, #0x8]
	str r4, [r0, #0x0]
	mov r0, #0x1
	add sp, sp, #0x10
	ldmia sp!, {r4-r6,pc}
	arm_func_end NNSi_GfdFreeLnkVram

	arm_func_start NNSi_GfdAllocLnkVramAligned
NNSi_GfdAllocLnkVramAligned: ; 0x020AF488
	stmdb sp!, {r4-r10,lr}
	ldr r4, [r0, #0x0]
	ldr r9, [sp, #0x20]
	cmp r4, #0x0
	mov r5, #0x0
	beq _020AF4EC
	sub r12, r9, #0x1
	mvn lr, r12
_020AF4A8:
	cmp r9, #0x1
	ldrls r8, [r4, #0x0]
	movls r6, r5
	movls r7, r3
	bls _020AF4D0
	ldr r7, [r4, #0x0]
	add r6, r7, r12
	and r8, lr, r6
	sub r6, r8, r7
	add r7, r3, r6
_020AF4D0:
	ldr r10, [r4, #0x4]
	cmp r10, r7
	movcs r5, r4
	bhs _020AF4EC
	ldr r4, [r4, #0xc]
	cmp r4, #0x0
	bne _020AF4A8
_020AF4EC:
	cmp r5, #0x0
	beq _020AF5B8
	cmp r6, #0x0
	beq _020AF54C
	ldr r9, [r1, #0x0]
	cmp r9, #0x0
	ldrne r3, [r9, #0xc]
	strne r3, [r1, #0x0]
	cmp r9, #0x0
	beq _020AF5B8
	ldr r4, [r5, #0x0]
	mov r3, #0x0
	str r4, [r9, #0x0]
	str r6, [r9, #0x4]
	str r3, [r9, #0x8]
	str r3, [r9, #0xc]
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	strne r9, [r3, #0x8]
	ldr r4, [r0, #0x0]
	mov r3, #0x0
	str r4, [r9, #0xc]
	str r3, [r9, #0x8]
	str r9, [r0, #0x0]
_020AF54C:
	ldr r3, [r5, #0x4]
	sub r3, r3, r7
	str r3, [r5, #0x4]
	ldr r3, [r5, #0x0]
	add r3, r3, r7
	str r3, [r5, #0x0]
	ldr r3, [r5, #0x4]
	cmp r3, #0x0
	bne _020AF5AC
	ldr r4, [r5, #0x8]
	ldr r3, [r5, #0xc]
	cmp r4, #0x0
	strne r3, [r4, #0xc]
	streq r3, [r0, #0x0]
	cmp r3, #0x0
	strne r4, [r3, #0x8]
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	strne r5, [r0, #0x8]
	ldr r3, [r1, #0x0]
	mov r0, #0x0
	str r3, [r5, #0xc]
	str r0, [r5, #0x8]
	str r5, [r1, #0x0]
_020AF5AC:
	str r8, [r2, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r10,pc}
_020AF5B8:
	mov r0, #0x0
	str r0, [r2, #0x0]
	ldmia sp!, {r4-r10,pc}
	arm_func_end NNSi_GfdAllocLnkVramAligned

	arm_func_start NNSi_GfdAllocLnkVram
NNSi_GfdAllocLnkVram: ; 0x020AF5C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	str r12, [sp, #0x0]
	bl NNSi_GfdAllocLnkVramAligned
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNSi_GfdAllocLnkVram

	arm_func_start NNSi_GfdAddNewFreeBlock
NNSi_GfdAddNewFreeBlock: ; 0x020AF5E0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, [r1, #0x0]
	cmp lr, #0x0
	ldrne r12, [lr, #0xc]
	strne r12, [r1, #0x0]
	cmp lr, #0x0
	beq _020AF640
	str r2, [lr, #0x0]
	str r3, [lr, #0x4]
	mov r1, #0x0
	str r1, [lr, #0x8]
	str r1, [lr, #0xc]
	ldr r1, [r0, #0x0]
	add sp, sp, #0x4
	cmp r1, #0x0
	strne lr, [r1, #0x8]
	ldr r2, [r0, #0x0]
	mov r1, #0x0
	str r2, [lr, #0xc]
	str r1, [lr, #0x8]
	str lr, [r0, #0x0]
	mov r0, #0x1
	ldmia sp!, {pc}
_020AF640:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNSi_GfdAddNewFreeBlock

	arm_func_start NNSi_GfdInitLnkVramBlockPool
NNSi_GfdInitLnkVramBlockPool: ; 0x020AF64C
	stmdb sp!, {r4,lr}
	subs lr, r1, #0x1
	mov r2, #0x0
	beq _020AF684
	mov r4, r0
_020AF660:
	add r12, r2, #0x1
	add r2, r0, r2, lsl #0x4
	add r3, r0, r12, lsl #0x4
	str r3, [r2, #0xc]
	str r4, [r3, #0x8]
	mov r2, r12
	cmp r12, lr
	add r4, r4, #0x10
	blo _020AF660
_020AF684:
	mov r2, #0x0
	str r2, [r0, #0x8]
	add r1, r0, r1, lsl #0x4
	str r2, [r1, #-0x4]
	ldmia sp!, {r4,pc}
	arm_func_end NNSi_GfdInitLnkVramBlockPool

	arm_func_start NNSi_GfdInitLnkVramMan
NNSi_GfdInitLnkVramMan: ; 0x020AF698
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	arm_func_end NNSi_GfdInitLnkVramMan
