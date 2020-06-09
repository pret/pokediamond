    .include "asm/macros.inc"
    .include "global.inc"

    .section .bss

	.global _03807920
_03807920: ;0x03807920
	.space 0x03807924 - 0x03807920

	.global OSi_NeedResetTimer
OSi_NeedResetTimer: ;0x03807924
	.space 0x03807928 - 0x03807924

	.global OSi_TickCounter
OSi_TickCounter: ;0x03807928
	.space 0x03807930 - 0x03807928

    .section .text

	arm_func_start OS_GetTick
OS_GetTick: ; 0x037FA364
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	bl	OS_DisableInterrupts
	ldr	r1, _037FA404	; =0x04000100
	ldrh	r1, [r1]
	strh	r1, [sp]
	ldr	r1, _037FA408	; =OSi_TickCounter
	ldr	ip, [r1]
	ldr	r3, [r1, #4]
	ldr	r2, _037FA40C	; =0x0000FFFF
	mvn	r1, #0
	and	r2, r3, r2
	and	r1, ip, r1
	str	r1, [sp, #4]
	str	r2, [sp, #8]
	ldr	r1, _037FA410	; =0x04000214
	ldr	r1, [r1]
	ands	r1, r1, #8
	beq	_037FA3D8
	ldrh	r1, [sp]
	ands	r1, r1, #32768	; 0x8000
	bne	_037FA3D8
	ldr	r3, [sp, #4]
	ldr	r2, [sp, #8]
	mov	r1, #1
	adds	r3, r3, r1
	adc	r1, r2, #0
	str	r3, [sp, #4]
	str	r1, [sp, #8]
_037FA3D8:
	bl	OS_RestoreInterrupts
	ldr	r2, [sp, #4]
	ldr	r0, [sp, #8]
	mov	r1, r0, lsl #16
	orr	r1, r1, r2, lsr #16
	ldrh	r0, [sp]
	orr	r1, r1, r0, asr #31
	orr	r0, r0, r2, lsl #16
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_037FA404:	.word	0x04000100
_037FA408:	.word	OSi_TickCounter
_037FA40C:	.word	0x0000FFFF
_037FA410:	.word	0x04000214

	arm_func_start OSi_CountUpTick
OSi_CountUpTick: ; 0x037FA414
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037FA488	; =OSi_TickCounter
	ldr	ip, [r1]
	ldr	r2, [r1, #4]
	mov	r3, #0
	mov	r0, #1
	adds	ip, ip, r0
	adc	r0, r2, #0
	str	ip, [r1]
	str	r0, [r1, #4]
	ldr	r0, _037FA48C	; =OSi_NeedResetTimer
	ldr	r1, [r0]
	cmp	r1, #0
	beq	_037FA46C
	ldr	r2, _037FA490	; =0x04000102
	strh	r3, [r2]
	ldr	r1, _037FA494	; =0x04000100
	strh	r3, [r1]
	mov	r1, #193	; 0xc1
	strh	r1, [r2]
	str	r3, [r0]
_037FA46C:
	mov	r0, #0
	ldr	r1, _037FA498	; =OSi_CountUpTick
	mov	r2, r0
	bl	OSi_EnterTimerCallback
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FA488:	.word	OSi_TickCounter
_037FA48C:	.word	OSi_NeedResetTimer
_037FA490:	.word	0x04000102
_037FA494:	.word	0x04000100
_037FA498:	.word	OSi_CountUpTick

	arm_func_start OS_IsTickAvailable
OS_IsTickAvailable: ; 0x037FA49C
	ldr	r0, _037FA4A8	; =_03807920
	ldrh	r0, [r0]
	bx	lr
_037FA4A8:	.word	_03807920

	arm_func_start OS_InitTick
OS_InitTick: ; 0x037FA4AC
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FA528	; =_03807920
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FA51C
	mov	r1, #1
	strh	r1, [r0]
	mov	r0, #0
	bl	OSi_SetTimerReserved
	mov	r2, #0
	ldr	r0, _037FA52C	; =OSi_TickCounter
	str	r2, [r0]
	str	r2, [r0, #4]
	ldr	r1, _037FA530	; =0x04000102
	strh	r2, [r1]
	ldr	r0, _037FA534	; =0x04000100
	strh	r2, [r0]
	mov	r0, #193	; 0xc1
	strh	r0, [r1]
	mov	r0, #8
	ldr	r1, _037FA538	; =OSi_CountUpTick
	bl	OS_SetIrqFunction
	mov	r0, #8
	bl	OS_EnableIrqMask
	mov	r1, #0
	ldr	r0, _037FA53C	; =OSi_NeedResetTimer
	str	r1, [r0]
_037FA51C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FA528:	.word	_03807920
_037FA52C:	.word	OSi_TickCounter
_037FA530:	.word	0x04000102
_037FA534:	.word	0x04000100
_037FA538:	.word	OSi_CountUpTick
_037FA53C:	.word	OSi_NeedResetTimer
