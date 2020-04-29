    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OSi_DequeueItem
OSi_DequeueItem: ; 0x020CBE9C
	ldr r2, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r2, #0x0
	streq r1, [r0, #0x8c]
	strne r1, [r2, #0x14]
	cmp r1, #0x0
	streq r2, [r0, #0x88]
	strne r2, [r1, #0x10]
	bx lr

	arm_func_start OSi_EnqueueTail
OSi_EnqueueTail: ; 0x020CBEC0
	ldr r2, [r0, #0x8c]
	cmp r2, #0x0
	streq r1, [r0, #0x88]
	strne r1, [r2, #0x10]
	str r2, [r1, #0x14]
	mov r2, #0x0
	str r2, [r1, #0x10]
	str r1, [r0, #0x8c]
	bx lr

	arm_func_start OS_TryLockMutex
OS_TryLockMutex: ; 0x020CBEE4
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r2, [r5, #0x8]
	ldr r1, _020CBF54 ; =OSi_ThreadInfo
	mov r4, r0
	cmp r2, #0x0
	ldr r0, [r1, #0x4]
	bne _020CBF28
	str r0, [r5, #0x8]
	ldr r2, [r5, #0xc]
	mov r1, r5
	add r2, r2, #0x1
	str r2, [r5, #0xc]
	bl OSi_EnqueueTail
	mov r6, #0x1
	b _020CBF40
_020CBF28:
	cmp r2, r0
	ldreq r0, [r5, #0xc]
	moveq r6, #0x1
	addeq r0, r0, #0x1
	streq r0, [r5, #0xc]
	movne r6, #0x0
_020CBF40:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r6
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CBF54: .word OSi_ThreadInfo

	arm_func_start OSi_UnlockAllMutex
OSi_UnlockAllMutex: ; 0x020CBF58
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, [r6, #0x88]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	add r5, r6, #0x88
	mov r4, #0x0
_020CBF78:
	mov r0, r5
	bl OSi_RemoveMutexLinkFromQueue
	str r4, [r0, #0xc]
	str r4, [r0, #0x8]
	bl OS_WakeupThread
	ldr r0, [r6, #0x88]
	cmp r0, #0x0
	bne _020CBF78
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start OS_UnlockMutex
OS_UnlockMutex: ; 0x020CBFA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CC00C ; =OSi_ThreadInfo
	mov r4, r0
	ldr r0, [r1, #0x4]
	ldr r1, [r5, #0x8]
	cmp r1, r0
	bne _020CBFF8
	ldr r1, [r5, #0xc]
	sub r1, r1, #0x1
	str r1, [r5, #0xc]
	ldr r1, [r5, #0xc]
	cmp r1, #0x0
	bne _020CBFF8
	mov r1, r5
	bl OSi_DequeueItem
	mov r1, #0x0
	mov r0, r5
	str r1, [r5, #0x8]
	bl OS_WakeupThread
_020CBFF8:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CC00C: .word OSi_ThreadInfo

	arm_func_start OS_LockMutex
OS_LockMutex: ; 0x020CC010
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CC098 ; =OSi_ThreadInfo
	mov r4, r0
	ldr r7, [r1, #0x4]
	mov r6, #0x0
_020CC030:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bne _020CC05C
	str r7, [r5, #0x8]
	ldr r1, [r5, #0xc]
	mov r0, r7
	add r2, r1, #0x1
	mov r1, r5
	str r2, [r5, #0xc]
	bl OSi_EnqueueTail
	b _020CC084
_020CC05C:
	cmp r0, r7
	ldreq r0, [r5, #0xc]
	addeq r0, r0, #0x1
	streq r0, [r5, #0xc]
	beq _020CC084
	mov r0, r5
	str r5, [r7, #0x84]
	bl OS_SleepThread
	str r6, [r7, #0x84]
	b _020CC030
_020CC084:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CC098: .word OSi_ThreadInfo

	arm_func_start OS_InitMutex
OS_InitMutex: ; 0x020CC09C
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0x8]
	str r2, [r0, #0xc]
	bx lr
