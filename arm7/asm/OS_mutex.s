	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OSi_DequeueItem
OSi_DequeueItem: ; 0x037F99E8
	ldr	r2, [r1, #16]
	ldr	r1, [r1, #20]
	cmp	r2, #0
	streq	r1, [r0, #112]	; 0x70
	strne	r1, [r2, #20]
	cmp	r1, #0
	streq	r2, [r0, #108]	; 0x6c
	strne	r2, [r1, #16]
	bx	lr

	arm_func_start OSi_EnqueueTail
OSi_EnqueueTail: ; 0x037F9A0C
	ldr	r2, [r0, #112]	; 0x70
	cmp	r2, #0
	streq	r1, [r0, #108]	; 0x6c
	strne	r1, [r2, #16]
	str	r2, [r1, #20]
	mov	r2, #0
	str	r2, [r1, #16]
	str	r1, [r0, #112]	; 0x70
	bx	lr

	arm_func_start OSi_UnlockAllMutex
OSi_UnlockAllMutex: ; 0x037F9A30
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	add	r5, r6, #108	; 0x6c
	mov	r4, #0
	b	_037F9A58
_037F9A44:
	mov	r0, r5
	bl	OSi_RemoveMutexLinkFromQueue
	str	r4, [r0, #12]
	str	r4, [r0, #8]
	bl	OS_WakeupThread
_037F9A58:
	ldr	r0, [r6, #108]	; 0x6c
	cmp	r0, #0
	bne	_037F9A44
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start OS_UnlockMutex
OS_UnlockMutex: ; 0x037F9A6C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, _037F9AD8	; =OSi_ThreadInfo
	ldr	r0, [r0, #4]
	ldr	r1, [r5, #8]
	cmp	r1, r0
	bne	_037F9AC4
	ldr	r1, [r5, #12]
	sub	r1, r1, #1
	str	r1, [r5, #12]
	ldr	r1, [r5, #12]
	cmp	r1, #0
	bne	_037F9AC4
	mov	r1, r5
	bl	OSi_DequeueItem
	mov	r0, #0
	str	r0, [r5, #8]
	mov	r0, r5
	bl	OS_WakeupThread
_037F9AC4:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F9AD8:	.word	OSi_ThreadInfo

	arm_func_start OS_LockMutex
OS_LockMutex: ; 0x037F9ADC
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r0, _037F9B64	; =OSi_ThreadInfo
	ldr	r7, [r0, #4]
	mov	r6, #0
_037F9AFC:
	ldr	r0, [r5, #8]
	cmp	r0, #0
	bne	_037F9B28
	str	r7, [r5, #8]
	ldr	r0, [r5, #12]
	add	r0, r0, #1
	str	r0, [r5, #12]
	mov	r0, r7
	mov	r1, r5
	bl	OSi_EnqueueTail
	b	_037F9B50
_037F9B28:
	cmp	r0, r7
	ldreq	r0, [r5, #12]
	addeq	r0, r0, #1
	streq	r0, [r5, #12]
	beq	_037F9B50
	str	r5, [r7, #104]	; 0x68
	mov	r0, r5
	bl	OS_SleepThread
	str	r6, [r7, #104]	; 0x68
	b	_037F9AFC
_037F9B50:
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037F9B64:	.word	OSi_ThreadInfo

	arm_func_start OS_InitMutex
OS_InitMutex: ; 0x037F9B68
	mov	r2, #0
	str	r2, [r0, #4]
	ldr	r1, [r0, #4]
	str	r1, [r0]
	str	r2, [r0, #8]
	str	r2, [r0, #12]
	bx	lr
