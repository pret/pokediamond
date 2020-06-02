	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OSi_AlarmHandler
OSi_AlarmHandler: ; 0x037FA540
	stmdb	sp!, {r0, lr}
	bl	OSi_ArrangeTimer
	ldmia	sp!, {r0, lr}
	bx	lr

	arm_func_start OSi_ArrangeTimer
OSi_ArrangeTimer: ; 0x037FA550
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r1, #0
	ldr	r0, _037FA644	; =0x04000106
	strh	r1, [r0]
	mov	r0, #16
	bl	OS_DisableIrqMask
	ldr	r1, _037FA648	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, #16
	str	r0, [r1]
	bl	OS_GetTick
	ldr	r2, _037FA64C	; =_03807934
	ldr	r4, [r2]
	cmp	r4, #0
	beq	_037FA638
	ldr	ip, [r4, #12]
	ldr	r3, [r4, #16]
	cmp	r1, r3
	cmpeq	r0, ip
	bcs	_037FA5B0
	mov	r0, r4
	bl	OSi_SetTimer
	b	_037FA638
_037FA5B0:
	ldr	r1, [r4, #24]
	str	r1, [r2]
	cmp	r1, #0
	moveq	r0, #0
	streq	r0, [r2, #4]
	movne	r0, #0
	strne	r0, [r1, #20]
	ldr	r5, [r4]
	ldr	r2, [r4, #28]
	ldr	r1, [r4, #32]
	mov	r0, #0
	cmp	r1, r0
	cmpeq	r2, r0
	streq	r0, [r4]
	cmp	r5, #0
	beq	_037FA5FC
	ldr	r0, [r4, #4]
	mov	lr, pc
	bx	r5
_037FA5FC:
	ldr	r2, [r4, #28]
	ldr	r0, [r4, #32]
	mov	r1, #0
	cmp	r0, r1
	cmpeq	r2, r1
	beq	_037FA624
	str	r5, [r4]
	mov	r0, r4
	mov	r2, r1
	bl	OSi_InsertAlarm
_037FA624:
	ldr	r0, _037FA64C	; =_03807934
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FA638
	bl	OSi_SetTimer
_037FA638:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA644:	.word	0x04000106
_037FA648:	.word	0x0380FFF8
_037FA64C:	.word	_03807934

	arm_func_start OS_CancelAlarm
OS_CancelAlarm: ; 0x037FA650
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r1, [r5]
	cmp	r1, #0
	bne	_037FA678
	bl	OS_RestoreInterrupts
	b	_037FA6D0
_037FA678:
	ldr	r0, [r5, #24]
	cmp	r0, #0
	ldreq	r2, [r5, #20]
	ldreq	r1, _037FA6DC	; =_03807934
	streq	r2, [r1, #4]
	ldrne	r1, [r5, #20]
	strne	r1, [r0, #20]
	ldr	r1, [r5, #20]
	cmp	r1, #0
	strne	r0, [r1, #24]
	bne	_037FA6B8
	ldr	r1, _037FA6DC	; =_03807934
	str	r0, [r1]
	cmp	r0, #0
	beq	_037FA6B8
	bl	OSi_SetTimer
_037FA6B8:
	mov	r0, #0
	str	r0, [r5]
	str	r0, [r5, #28]
	str	r0, [r5, #32]
	mov	r0, r4
	bl	OS_RestoreInterrupts
_037FA6D0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA6DC:	.word	_03807934

	arm_func_start OS_SetPeriodicAlarm
OS_SetPeriodicAlarm: ; 0x037FA6E0
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	movs	r4, r0
	mov	r9, r1
	mov	r8, r2
	mov	r7, r3
	ldr	r6, [sp, #32]
	beq	_037FA70C
	ldr	r0, [r4]
	cmp	r0, #0
	beq	_037FA710
_037FA70C:
	bl	FUN_037FB1F0
_037FA710:
	bl	OS_DisableInterrupts
	mov	r5, r0
	str	r7, [r4, #28]
	str	r6, [r4, #32]
	str	r9, [r4, #36]	; 0x24
	str	r8, [r4, #40]	; 0x28
	ldr	r0, [sp, #36]	; 0x24
	str	r0, [r4]
	ldr	r0, [sp, #40]	; 0x28
	str	r0, [r4, #4]
	mov	r0, r4
	mov	r1, #0
	mov	r2, r1
	bl	OSi_InsertAlarm
	mov	r0, r5
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr

	arm_func_start OS_SetAlarm
OS_SetAlarm: ; 0x037FA75C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	movs	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r8, r3
	beq	_037FA780
	ldr	r0, [r7]
	cmp	r0, #0
	beq	_037FA784
_037FA780:
	bl	FUN_037FB1F0
_037FA784:
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #0
	str	r0, [r7, #28]
	str	r0, [r7, #32]
	str	r8, [r7]
	ldr	r0, [sp, #24]
	str	r0, [r7, #4]
	bl	OS_GetTick
	mov	r2, r0
	mov	r0, r7
	adds	r3, r6, r2
	adc	r2, r5, r1
	mov	r1, r3
	bl	OSi_InsertAlarm
	mov	r0, r4
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start OSi_InsertAlarm
OSi_InsertAlarm: ; 0x037FA7D0
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	ldr	r2, [r8, #28]
	ldr	r1, [r8, #32]
	mov	r0, #0
	cmp	r1, r0
	cmpeq	r2, r0
	beq	_037FA84C
	bl	OS_GetTick
	ldr	r7, [r8, #36]	; 0x24
	ldr	r6, [r8, #40]	; 0x28
	cmp	r6, r1
	cmpeq	r7, r0
	bcs	_037FA84C
	ldr	r5, [r8, #28]
	ldr	r4, [r8, #32]
	subs	r0, r0, r7
	sbc	r1, r1, r6
	mov	r2, r5
	mov	r3, r4
	bl	_ll_udiv
	mov	r2, #1
	adds	r2, r0, r2
	adc	r0, r1, #0
	umull	r3, r1, r5, r2
	mla	r1, r5, r0, r1
	mla	r1, r4, r2, r1
	adds	r7, r7, r3
	adc	r6, r6, r1
_037FA84C:
	str	r7, [r8, #12]
	str	r6, [r8, #16]
	ldr	r0, _037FA8FC	; =_03807934
	ldr	r4, [r0]
	mov	r1, #0
	b	_037FA8B8
_037FA864:
	ldr	r2, [r4, #12]
	ldr	r0, [r4, #16]
	subs	r3, r7, r2
	sbc	r2, r6, r0
	subs	r0, r3, r1
	sbcs	r0, r2, r1
	bge	_037FA8B4
	ldr	r0, [r4, #20]
	str	r0, [r8, #20]
	str	r8, [r4, #20]
	str	r4, [r8, #24]
	ldr	r0, [r8, #20]
	cmp	r0, #0
	strne	r8, [r0, #24]
	bne	_037FA8F4
	ldr	r0, _037FA8FC	; =_03807934
	str	r8, [r0]
	mov	r0, r8
	bl	OSi_SetTimer
	b	_037FA8F4
_037FA8B4:
	ldr	r4, [r4, #24]
_037FA8B8:
	cmp	r4, #0
	bne	_037FA864
	mov	r0, #0
	str	r0, [r8, #24]
	ldr	r0, _037FA8FC	; =_03807934
	ldr	r1, [r0, #4]
	str	r8, [r0, #4]
	str	r1, [r8, #20]
	cmp	r1, #0
	strne	r8, [r1, #24]
	bne	_037FA8F4
	str	r8, [r0, #4]
	str	r8, [r0]
	mov	r0, r8
	bl	OSi_SetTimer
_037FA8F4:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FA8FC:	.word	_03807934

	arm_func_start OS_CreateAlarm
OS_CreateAlarm: ; 0x037FA900
	mov	r1, #0
	str	r1, [r0]
	str	r1, [r0, #8]
	bx	lr

	arm_func_start OS_IsAlarmAvailable
OS_IsAlarmAvailable: ; 0x037FA910
	ldr	r0, _037FA91C	; =_03807930
	ldrh	r0, [r0]
	bx	lr
_037FA91C:	.word	_03807930

	arm_func_start OS_InitAlarm
OS_InitAlarm: ; 0x037FA920
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FA968	; =_03807930
	ldrh	r0, [r1]
	cmp	r0, #0
	bne	_037FA95C
	mov	r0, #1
	strh	r0, [r1]
	bl	OSi_SetTimerReserved
	mov	r1, #0
	ldr	r0, _037FA96C	; =_03807934
	str	r1, [r0]
	str	r1, [r0, #4]
	mov	r0, #16
	bl	OS_DisableIrqMask
_037FA95C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FA968:	.word	_03807930
_037FA96C:	.word	_03807934

	arm_func_start OSi_SetTimer
OSi_SetTimer: ; 0x037FA970
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	bl	OS_GetTick
	mov	r2, #0
	ldr	r3, _037FA9FC	; =0x04000106
	strh	r2, [r3]
	ldr	ip, [r4, #12]
	ldr	r3, [r4, #16]
	subs	r5, ip, r0
	sbc	r4, r3, r1
	mov	r0, #1
	ldr	r1, _037FAA00	; =OSi_AlarmHandler
	bl	OSi_EnterTimerCallback
	mov	r1, #0
	subs	r0, r5, r1
	sbcs	r0, r4, r1
	ldrlt	r1, _037FAA04	; =0x0000FFFE
	blt	_037FA9D4
	mov	r0, #65536	; 0x10000
	subs	r0, r5, r0
	sbcs	r0, r4, r1
	mvnlt	r0, r5
	movlt	r0, r0, lsl #16
	movlt	r1, r0, lsr #16
_037FA9D4:
	ldr	r0, _037FAA08	; =0x04000104
	strh	r1, [r0]
	mov	r1, #193	; 0xc1
	ldr	r0, _037FA9FC	; =0x04000106
	strh	r1, [r0]
	mov	r0, #16
	bl	OS_EnableIrqMask
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA9FC:	.word	0x04000106
_037FAA00:	.word	OSi_AlarmHandler
_037FAA04:	.word	0x0000FFFE
_037FAA08:	.word	0x04000104
