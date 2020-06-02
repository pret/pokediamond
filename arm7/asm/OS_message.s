	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OS_ReadMessage
OS_ReadMessage: ; 0x037F980C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	and	r8, r7, #1
	add	r7, r6, #8
	b	_037F9850
_037F9830:
	cmp	r8, #0
	bne	_037F9848
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F987C
_037F9848:
	mov	r0, r7
	bl	OS_SleepThread
_037F9850:
	ldr	r0, [r6, #28]
	cmp	r0, #0
	beq	_037F9830
	cmp	r5, #0
	ldrne	r1, [r6, #16]
	ldrne	r0, [r6, #24]
	ldrne	r0, [r1, r0, lsl #2]
	strne	r0, [r5]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F987C:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start OS_ReceiveMessage
OS_ReceiveMessage: ; 0x037F9884
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	and	r8, r7, #1
	add	r7, r6, #8
	b	_037F98C8
_037F98A8:
	cmp	r8, #0
	bne	_037F98C0
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F991C
_037F98C0:
	mov	r0, r7
	bl	OS_SleepThread
_037F98C8:
	ldr	r0, [r6, #28]
	cmp	r0, #0
	beq	_037F98A8
	cmp	r5, #0
	ldrne	r1, [r6, #16]
	ldrne	r0, [r6, #24]
	ldrne	r0, [r1, r0, lsl #2]
	strne	r0, [r5]
	ldr	r0, [r6, #24]
	add	r0, r0, #1
	ldr	r1, [r6, #20]
	bl	_s32_div_f
	str	r1, [r6, #24]
	ldr	r0, [r6, #28]
	sub	r0, r0, #1
	str	r0, [r6, #28]
	mov	r0, r6
	bl	OS_WakeupThread
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F991C:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start OS_SendMessage
OS_SendMessage: ; 0x037F9924
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	and	r7, r7, #1
	b	_037F9968
_037F9948:
	cmp	r7, #0
	bne	_037F9960
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037F99AC
_037F9960:
	mov	r0, r6
	bl	OS_SleepThread
_037F9968:
	ldr	r2, [r6, #28]
	ldr	r1, [r6, #20]
	cmp	r1, r2
	ble	_037F9948
	ldr	r0, [r6, #24]
	add	r0, r0, r2
	bl	_s32_div_f
	ldr	r0, [r6, #16]
	str	r5, [r0, r1, lsl #2]
	ldr	r0, [r6, #28]
	add	r0, r0, #1
	str	r0, [r6, #28]
	add	r0, r6, #8
	bl	OS_WakeupThread
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #1
_037F99AC:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start OS_InitMessageQueue
OS_InitMessageQueue: ; 0x037F99B8
	mov	ip, #0
	str	ip, [r0, #4]
	ldr	r3, [r0, #4]
	str	r3, [r0]
	str	ip, [r0, #12]
	ldr	r3, [r0, #12]
	str	r3, [r0, #8]
	str	r1, [r0, #16]
	str	r2, [r0, #20]
	str	ip, [r0, #24]
	str	ip, [r0, #28]
	bx	lr
