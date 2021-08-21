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

	arm_func_start NNS_FndAllocFromExpHeapEx
NNS_FndAllocFromExpHeapEx: ; 0x020ADFA0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	moveq r1, #0x1
	add r1, r1, #0x3
	cmp r2, #0x0
	bic r1, r1, #0x3
	blt _020ADFCC
	bl AllocFromHead
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADFCC:
	rsb r2, r2, #0x0
	bl AllocFromTail
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndAllocFromExpHeapEx

	arm_func_start NNS_FndDestroyExpHeap
NNS_FndDestroyExpHeap: ; 0x020ADFDC
	ldr ip, _020ADFE4 ; =NNSi_FndFinalizeHeap
	bx r12
	.balign 4
_020ADFE4: .word NNSi_FndFinalizeHeap
	arm_func_end NNS_FndDestroyExpHeap

	arm_func_start NNS_FndCreateExpHeapEx
NNS_FndCreateExpHeapEx: ; 0x020ADFE8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	add r1, r1, r0
	add r0, r0, #0x3
	bic r1, r1, #0x3
	bic r0, r0, #0x3
	cmp r0, r1
	bhi _020AE014
	sub r3, r1, r0
	cmp r3, #0x4c
	bhs _020AE020
_020AE014:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020AE020:
	bl InitExpHeap
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndCreateExpHeapEx

	arm_func_start RecycleRegion
RecycleRegion:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r1
	ldr r2, [r5, #0x0]
	ldr r1, [r5, #0x4]
	mov r6, r0
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [r6, #0x0]
	mov r4, #0x0
	cmp r1, #0x0
	beq _020AE0A0
	ldr r0, [r5, #0x0]
_020AE060:
	cmp r1, r0
	movcc r4, r1
	blo _020AE094
	ldr r0, [r5, #0x4]
	cmp r1, r0
	bne _020AE0A0
	ldr r2, [r1, #0x4]
	add r0, r1, #0x10
	add r2, r2, r0
	mov r0, r6
	str r2, [sp, #0x4]
	bl RemoveMBlock
	b _020AE0A0
_020AE094:
	ldr r1, [r1, #0xc]
	cmp r1, #0x0
	bne _020AE060
_020AE0A0:
	cmp r4, #0x0
	beq _020AE0D4
	ldr r2, [r4, #0x4]
	add r1, r4, #0x10
	ldr r0, [r5, #0x0]
	add r1, r2, r1
	cmp r1, r0
	bne _020AE0D4
	mov r0, r6
	mov r1, r4
	str r4, [sp, #0x0]
	bl RemoveMBlock
	mov r4, r0
_020AE0D4:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r0, r1, r0
	cmp r0, #0x10
	addcc sp, sp, #0x8
	movcc r0, #0x0
	ldmccia sp!, {r4-r6,pc}
	ldr r1, _020AE118 ; =0x00004652
	add r0, sp, #0x0
	bl InitMBlock
	mov r1, r0
	mov r0, r6
	mov r2, r4
	bl InsertMBlock
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AE118: .word 0x00004652
	arm_func_end RecycleRegion
