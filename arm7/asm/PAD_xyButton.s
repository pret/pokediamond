	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start PAD_InitXYButton
PAD_InitXYButton: ; 0x037FB96C
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	bl	OS_IsTickAvailable
	cmp	r0, #0
	beq	_037FB98C
	bl	OS_IsAlarmAvailable
	cmp	r0, #0
	bne	_037FB994
_037FB98C:
	mov	r0, #0
	b	_037FB9F0
_037FB994:
	ldr	r0, _037FB9FC	; =PADi_XYButtonAvailable
	ldr	r0, [r0]
	cmp	r0, #0
	movne	r0, #0
	bne	_037FB9F0
	ldr	r0, _037FBA00	; =_038079E0
	bl	OS_CreateAlarm
	bl	OS_GetTick
	mov	r2, r0
	ldr	r0, _037FBA04	; =FUN_037FB92C
	str	r0, [sp, #4]
	mov	r0, #0
	str	r0, [sp, #8]
	ldr	r3, _037FBA08	; =0x0000082E
	str	r0, [sp]
	ldr	r0, _037FBA00	; =_038079E0
	adds	ip, r2, r3
	adc	r2, r1, #0
	mov	r1, ip
	bl	OS_SetPeriodicAlarm
	mov	r0, #1
	ldr	r1, _037FB9FC	; =PADi_XYButtonAvailable
	str	r0, [r1]
_037FB9F0:
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FB9FC:	.word	PADi_XYButtonAvailable
_037FBA00:	.word	_038079E0
_037FBA04:	.word	FUN_037FB92C
_037FBA08:	.word	0x0000082E
