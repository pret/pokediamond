	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OSi_GetVFrame
OSi_GetVFrame: ; 0x037FAA0C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	OS_DisableInterrupts
	ldr	r1, _037FAA50	; =_03807940
	ldr	r1, [r1]
	cmp	r4, r1
	ldrlt	r1, _037FAA54	; =_03807944
	ldrlt	r2, [r1]
	addlt	r2, r2, #1
	strlt	r2, [r1]
	ldr	r1, _037FAA50	; =_03807940
	str	r4, [r1]
	bl	OS_RestoreInterrupts
	ldr	r0, _037FAA54	; =_03807944
	ldr	r0, [r0]
	ldmia	sp!, {r4, lr}
	bx	lr
_037FAA50:	.word	_03807940
_037FAA54:	.word	_03807944

	arm_func_start OSi_CompareVCount
OSi_CompareVCount: ; 0x037FAA58
	ldr	r3, [r0, #12]
	subs	r3, r1, r3
	ldrsh	r1, [r0, #16]
	sub	r2, r2, r1
	bmi	_037FAA7C
	cmp	r3, #0
	bne	_037FAA84
	cmp	r2, #0
	bge	_037FAA84
_037FAA7C:
	mov	r0, #0
	bx	lr
_037FAA84:
	cmp	r2, #0
	ldrlt	r1, _037FAAA4	; =0x00000107
	addlt	r2, r2, r1
	ldrsh	r0, [r0, #18]
	cmp	r2, r0
	movle	r0, #1
	movgt	r0, #2
	bx	lr
_037FAAA4:	.word	0x00000107

	arm_func_start OSi_VAlarmHandler
OSi_VAlarmHandler: ; 0x037FAAA8
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	r0, #4
	bl	OS_DisableIrqMask
	ldr	r2, _037FAC1C	; =0x04000004
	ldrh	r0, [r2]
	bic	r0, r0, #32
	strh	r0, [r2]
	ldr	r1, _037FAC20	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, #4
	str	r0, [r1]
	ldrh	r2, [r2]
	mov	r0, r2, asr #8
	and	r1, r0, #255	; 0xff
	mov	r0, r2, lsl #1
	and	r0, r0, #256	; 0x100
	orr	r0, r1, r0
	sub	r0, r0, #1
	bl	OSi_GetVFrame
	ldr	r9, _037FAC24	; =0x04000006
	mov	r6, #4
	ldr	r5, _037FAC1C	; =0x04000004
	mov	r4, #0
	ldr	fp, _037FAC28	; =_03807944
	b	_037FAC00
_037FAB10:
	ldrh	r8, [r9]
	mov	r0, r8
	bl	OSi_GetVFrame
	mov	r7, r0
	mov	r0, sl
	mov	r1, r7
	mov	r2, r8
	bl	OSi_CompareVCount
	cmp	r0, #0
	beq	_037FAB4C
	cmp	r0, #1
	beq	_037FAB8C
	cmp	r0, #2
	beq	_037FABE4
	b	_037FAC00
_037FAB4C:
	mov	r0, sl
	bl	OSi_SetNextVAlarm
	ldrh	r1, [r9]
	ldrsh	r0, [sl, #16]
	cmp	r0, r1
	bne	_037FAC10
	ldr	r0, [sl, #12]
	cmp	r0, r7
	bne	_037FAC10
	mov	r0, r6
	bl	OS_DisableIrqMask
	ldrh	r0, [r5]
	bic	r0, r0, #32
	strh	r0, [r5]
	mov	r0, r6
	bl	OS_ResetRequestIrqMask
_037FAB8C:
	ldr	r7, [sl]
	mov	r0, sl
	bl	OSi_DetachVAlarm
	str	r4, [sl]
	cmp	r7, #0
	beq	_037FABB0
	ldr	r0, [sl, #4]
	mov	lr, pc
	bx	r7
_037FABB0:
	ldr	r0, [sl, #28]
	cmp	r0, #0
	beq	_037FAC00
	ldr	r0, [sl, #36]	; 0x24
	cmp	r0, #0
	bne	_037FAC00
	str	r7, [sl]
	ldr	r0, [fp]
	add	r0, r0, #1
	str	r0, [sl, #12]
	mov	r0, sl
	bl	OSi_AppendVAlarm
	b	_037FAC00
_037FABE4:
	mov	r0, sl
	bl	OSi_DetachVAlarm
	mov	r0, sl
	bl	OSi_AppendVAlarm
	ldr	r0, [fp]
	add	r0, r0, #1
	str	r0, [sl, #12]
_037FAC00:
	ldr	r0, _037FAC2C	; =_03807948
	ldr	sl, [r0]
	cmp	sl, #0
	bne	_037FAB10
_037FAC10:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FAC1C:	.word	0x04000004
_037FAC20:	.word	0x0380FFF8
_037FAC24:	.word	0x04000006
_037FAC28:	.word	_03807944
_037FAC2C:	.word	_03807948

	arm_func_start OS_CancelVAlarms
OS_CancelVAlarms: ; 0x037FAC30
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	bl	OS_DisableInterrupts
	mov	r5, r0
	cmp	r7, #0
	bne	_037FAC50
	bl	OS_Terminate
_037FAC50:
	ldr	r0, _037FACA8	; =_03807948
	ldr	r0, [r0]
	cmp	r0, #0
	ldrne	r6, [r0, #24]
	moveq	r6, #0
	mov	r4, #0
	b	_037FAC8C
_037FAC6C:
	ldr	r1, [r0, #8]
	cmp	r1, r7
	bne	_037FAC7C
	bl	OS_CancelVAlarm
_037FAC7C:
	mov	r0, r6
	cmp	r6, #0
	ldrne	r6, [r6, #24]
	moveq	r6, r4
_037FAC8C:
	cmp	r0, #0
	bne	_037FAC6C
	mov	r0, r5
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FACA8:	.word	_03807948

	arm_func_start OS_CancelVAlarm
OS_CancelVAlarm: ; 0x037FACAC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r1, #1
	str	r1, [r5, #36]	; 0x24
	ldr	r1, [r5]
	cmp	r1, #0
	bne	_037FACDC
	bl	OS_RestoreInterrupts
	b	_037FACF4
_037FACDC:
	mov	r0, r5
	bl	OSi_DetachVAlarm
	mov	r0, #0
	str	r0, [r5]
	mov	r0, r4
	bl	OS_RestoreInterrupts
_037FACF4:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start OS_SetVAlarmTag
OS_SetVAlarmTag: ; 0x037FAD00
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	movs	r4, r1
	bne	_037FAD18
	bl	OS_Terminate
_037FAD18:
	cmp	r5, #0
	strne	r4, [r5, #8]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start OSi_SetNextVAlarm
OSi_SetNextVAlarm: ; 0x037FAD2C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #4
	ldr	r1, _037FAD80	; =OSi_VAlarmHandler
	bl	OS_SetIrqFunction
	ldrsh	ip, [r4, #16]
	and	r3, ip, #256	; 0x100
	ldr	r1, _037FAD84	; =0x04000004
	ldrh	r0, [r1]
	and	r2, r0, #63	; 0x3f
	and	r0, ip, #255	; 0xff
	orr	r0, r2, r0, lsl #8
	orr	r0, r0, r3, asr #1
	strh	r0, [r1]
	ldrh	r0, [r1]
	orr	r0, r0, #32
	strh	r0, [r1]
	mov	r0, #4
	bl	OS_EnableIrqMask
	ldmia	sp!, {r4, lr}
	bx	lr
_037FAD80:	.word	OSi_VAlarmHandler
_037FAD84:	.word	0x04000004

	arm_func_start OS_SetPeriodicVAlarm
OS_SetPeriodicVAlarm: ; 0x037FAD88
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	cmp	r8, #0
	beq	_037FADBC
	ldr	r0, [r8]
	cmp	r0, #0
	beq	_037FADC0
_037FADBC:
	bl	OS_Terminate
_037FADC0:
	ldr	r0, _037FAE1C	; =0x04000006
	ldrh	r9, [r0]
	mov	r0, r9
	bl	OSi_GetVFrame
	mov	r1, #1
	str	r1, [r8, #28]
	strh	r7, [r8, #16]
	cmp	r7, r9
	addle	r0, r0, #1
	str	r0, [r8, #12]
	strh	r6, [r8, #18]
	str	r5, [r8]
	ldr	r0, [sp, #32]
	str	r0, [r8, #4]
	mov	r0, #0
	str	r0, [r8, #36]	; 0x24
	mov	r0, r8
	bl	OSi_InsertVAlarm
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FAE1C:	.word	0x04000006

	arm_func_start OS_SetVAlarm
OS_SetVAlarm: ; 0x037FAE20
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	bl	OS_DisableInterrupts
	mov	r4, r0
	cmp	r8, #0
	beq	_037FAE54
	ldr	r0, [r8]
	cmp	r0, #0
	beq	_037FAE58
_037FAE54:
	bl	OS_Terminate
_037FAE58:
	ldr	r0, _037FAEB4	; =0x04000006
	ldrh	r9, [r0]
	mov	r0, r9
	bl	OSi_GetVFrame
	mov	r1, #0
	str	r1, [r8, #28]
	strh	r7, [r8, #16]
	cmp	r7, r9
	addle	r0, r0, #1
	str	r0, [r8, #12]
	strh	r6, [r8, #18]
	str	r5, [r8]
	ldr	r0, [sp, #32]
	str	r0, [r8, #4]
	mov	r0, #0
	str	r0, [r8, #36]	; 0x24
	mov	r0, r8
	bl	OSi_InsertVAlarm
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FAEB4:	.word	0x04000006

	arm_func_start OS_CreateVAlarm
OS_CreateVAlarm: ; 0x037FAEB8
	mov	r1, #0
	str	r1, [r0]
	str	r1, [r0, #8]
	str	r1, [r0, #32]
	bx	lr

	arm_func_start OSi_DetachVAlarm
OSi_DetachVAlarm: ; 0x037FAECC
	cmp	r0, #0
	bxeq	lr
	ldr	r2, [r0, #20]
	ldr	r1, [r0, #24]
	cmp	r1, #0
	strne	r2, [r1, #20]
	ldreq	r0, _037FAF00	; =_03807948
	streq	r2, [r0, #4]
	cmp	r2, #0
	strne	r1, [r2, #24]
	ldreq	r0, _037FAF00	; =_03807948
	streq	r1, [r0]
	bx	lr
_037FAF00:	.word	_03807948

	arm_func_start OSi_AppendVAlarm
OSi_AppendVAlarm: ; 0x037FAF04
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FAF44	; =_03807948
	ldr	r3, [r1, #4]
	str	r3, [r0, #20]
	mov	r2, #0
	str	r2, [r0, #24]
	str	r0, [r1, #4]
	cmp	r3, #0
	strne	r0, [r3, #24]
	bne	_037FAF38
	str	r0, [r1]
	bl	OSi_SetNextVAlarm
_037FAF38:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FAF44:	.word	_03807948

	arm_func_start OSi_InsertVAlarm
OSi_InsertVAlarm: ; 0x037FAF48
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FAFCC	; =_03807948
	ldr	r3, [r1]
	b	_037FAFB4
_037FAF5C:
	ldr	r2, [r0, #12]
	ldr	r1, [r3, #12]
	cmp	r1, r2
	bcc	_037FAFB0
	cmp	r1, r2
	bne	_037FAF84
	ldrsh	r2, [r3, #16]
	ldrsh	r1, [r0, #16]
	cmp	r2, r1
	ble	_037FAFB0
_037FAF84:
	ldr	r1, [r3, #20]
	str	r1, [r0, #20]
	str	r3, [r0, #24]
	str	r0, [r3, #20]
	cmp	r1, #0
	strne	r0, [r1, #24]
	bne	_037FAFC0
	ldr	r1, _037FAFCC	; =_03807948
	str	r0, [r1]
	bl	OSi_SetNextVAlarm
	b	_037FAFC0
_037FAFB0:
	ldr	r3, [r3, #24]
_037FAFB4:
	cmp	r3, #0
	bne	_037FAF5C
	bl	OSi_AppendVAlarm
_037FAFC0:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FAFCC:	.word	_03807948

	arm_func_start OS_IsVAlarmAvailable
OS_IsVAlarmAvailable: ; 0x037FAFD0
	ldr	r0, _037FAFDC	; =_0380793C
	ldrh	r0, [r0]
	bx	lr
_037FAFDC:	.word	_0380793C

	arm_func_start OS_InitVAlarm
OS_InitVAlarm: ; 0x037FAFE0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FB038	; =_0380793C
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FB02C
	mov	r1, #1
	strh	r1, [r0]
	mov	r1, #0
	ldr	r0, _037FB03C	; =_03807948
	str	r1, [r0]
	str	r1, [r0, #4]
	mov	r0, #4
	bl	OS_DisableIrqMask
	mov	r1, #0
	ldr	r0, _037FB040	; =_03807944
	str	r1, [r0]
	ldr	r0, _037FB044	; =_03807940
	str	r1, [r0]
_037FB02C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB038:	.word	_0380793C
_037FB03C:	.word	_03807948
_037FB040:	.word	_03807944
_037FB044:	.word	_03807940
