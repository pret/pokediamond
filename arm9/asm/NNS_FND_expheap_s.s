	.include "asm/macros.inc"
	.include "global.inc"
	.extern NNSi_FndInitHeapHead
	.extern NNSi_FndFinalizeHeap
	.extern GetRegionOfMBlock
	.extern RemoveMBlock
	.extern InsertMBlock
	.extern InitMBlock
	.extern InitExpHeap
	.extern AllocUsedBlockFromFreeBlock
	.extern AllocFromHead
	.extern AllocFromTail
	.extern RecycleRegion
	.text

	arm_func_start NNS_FndGetSizeForMBlockExpHeap
NNS_FndGetSizeForMBlockExpHeap: ; 0x020ADDC0
	ldr r0, [r0, #-0xc]
	bx lr
	arm_func_end NNS_FndGetSizeForMBlockExpHeap

	arm_func_start NNS_FndGetTotalFreeSizeForExpHeap
NNS_FndGetTotalFreeSizeForExpHeap: ; 0x020ADDC8
	ldr r2, [r0, #0x24]
	mov r0, #0x0
	cmp r2, #0x0
	bxeq lr
_020ADDD8:
	ldr r1, [r2, #0x4]
	ldr r2, [r2, #0xc]
	add r0, r0, r1
	cmp r2, #0x0
	bne _020ADDD8
	bx lr
	arm_func_end NNS_FndGetTotalFreeSizeForExpHeap

	arm_func_start NNS_FndFreeToExpHeap
NNS_FndFreeToExpHeap: ; 0x020ADDF0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	sub r4, r1, #0x10
	add r5, r0, #0x24
	add r0, sp, #0x0
	mov r1, r4
	bl GetRegionOfMBlock
	mov r1, r4
	add r0, r5, #0x8
	bl RemoveMBlock
	add r1, sp, #0x0
	mov r0, r5
	bl RecycleRegion
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}
	arm_func_end NNS_FndFreeToExpHeap

	arm_func_start NNS_FndResizeForMBlockExpHeap
NNS_FndResizeForMBlockExpHeap: ; 0x020ADE2C
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x10
	mov r4, r1
	mov r10, r2
	sub r6, r4, #0x10
	add r1, r10, #0x3
	mov r5, r0
	ldr r8, [r6, #0x4]
	bic r10, r1, #0x3
	cmp r10, r8
	add r7, r5, #0x24
	addeq sp, sp, #0x10
	moveq r0, r10
	ldmeqia sp!, {r4-r10,pc}
	cmp r10, r8
	bls _020ADF60
	ldr r9, [r7, #0x0]
	add r0, r6, #0x10
	cmp r9, #0x0
	add r0, r8, r0
	beq _020ADE94
_020ADE80:
	cmp r9, r0
	beq _020ADE94
	ldr r9, [r9, #0xc]
	cmp r9, #0x0
	bne _020ADE80
_020ADE94:
	cmp r9, #0x0
	beq _020ADEB0
	ldr r0, [r9, #0x4]
	add r1, r8, #0x10
	add r0, r1, r0
	cmp r10, r0
	bls _020ADEBC
_020ADEB0:
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r10,pc}
_020ADEBC:
	add r0, sp, #0x0
	mov r1, r9
	bl GetRegionOfMBlock
	mov r0, r7
	mov r1, r9
	bl RemoveMBlock
	ldr r2, [sp, #0x4]
	add r3, r10, r4
	ldr r9, [sp, #0x0]
	sub r1, r2, r3
	str r3, [sp, #0x0]
	cmp r1, #0x10
	strcc r2, [sp, #0x0]
	mov r8, r0
	ldr r0, [sp, #0x0]
	sub r0, r0, r4
	str r0, [r6, #0x4]
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r0, r1, r0
	cmp r0, #0x10
	blo _020ADF30
	ldr r1, _020ADF9C ; =0x00004652
	add r0, sp, #0x0
	bl InitMBlock
	mov r1, r0
	mov r0, r7
	mov r2, r8
	bl InsertMBlock
_020ADF30:
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #0x0]
	and r0, r0, #0xff
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	sub r2, r1, r9
	ands r0, r0, #0x1
	beq _020ADF90
	mov r1, r9
	mov r0, #0x0
	bl MIi_CpuClear32
	b _020ADF90
_020ADF60:
	add r0, r10, r4
	str r0, [sp, #0x8]
	ldr r1, [r6, #0x4]
	add r0, r6, #0x10
	add r0, r1, r0
	str r0, [sp, #0xc]
	add r1, sp, #0x8
	mov r0, r7
	str r10, [r6, #0x4]
	bl RecycleRegion
	cmp r0, #0x0
	streq r8, [r6, #0x4]
_020ADF90:
	ldr r0, [r6, #0x4]
	add sp, sp, #0x10
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020ADF9C: .word 0x00004652
	arm_func_end NNS_FndResizeForMBlockExpHeap
