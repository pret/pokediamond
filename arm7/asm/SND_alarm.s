	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03808EEC
_03808EEC: ;0x03808EEC
	.space 0x038090EC - 0x03808EEC

    .section .text

	arm_func_start AlarmHandler
AlarmHandler: ; 0x037FF524
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, #7
	mov	r4, #0
_037FF534:
	mov	r0, r5
	mov	r1, r6
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_037FF534
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start SND_StopAlarm
SND_StopAlarm: ; 0x037FF554
	stmdb	sp!, {r4, lr}
	ldr	r1, _037FF590	; =_03808EEC
	add	r4, r1, r0, lsl #6
	ldrb	r0, [r1, r0, lsl #6]
	cmp	r0, #0
	beq	_037FF588
	add	r0, r4, #20
	bl	OS_CancelAlarm
	ldrb	r0, [r4, #1]
	add	r0, r0, #1
	strb	r0, [r4, #1]
	mov	r0, #0
	strb	r0, [r4]
_037FF588:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FF590:	.word	_03808EEC

	arm_func_start SND_StartAlarm
SND_StartAlarm: ; 0x037FF594
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #12
	mov	r4, r0
	ldr	r0, _037FF654	; =_03808EEC
	add	r5, r0, r4, lsl #6
	ldrb	r0, [r0, r4, lsl #6]
	cmp	r0, #0
	beq	_037FF5C4
	add	r0, r5, #20
	bl	OS_CancelAlarm
	mov	r0, #0
	strb	r0, [r5]
_037FF5C4:
	ldr	r9, [r5, #4]
	ldr	r8, [r5, #8]
	ldr	r7, [r5, #12]
	ldr	r6, [r5, #16]
	ldrb	r0, [r5, #1]
	orr	r4, r4, r0, lsl #8
	add	r0, r5, #20
	bl	OS_CreateAlarm
	mov	r0, #0
	cmp	r6, r0
	cmpeq	r7, r0
	bne	_037FF610
	str	r4, [sp]
	add	r0, r5, #20
	mov	r1, r9
	mov	r2, r8
	ldr	r3, _037FF658	; =AlarmHandler
	bl	OS_SetAlarm
	b	_037FF640
_037FF610:
	bl	OS_GetTick
	mov	r2, r0
	ldr	r0, _037FF658	; =AlarmHandler
	str	r0, [sp, #4]
	str	r4, [sp, #8]
	mov	r3, r7
	str	r6, [sp]
	add	r0, r5, #20
	adds	r4, r9, r2
	adc	r2, r8, r1
	mov	r1, r4
	bl	OS_SetPeriodicAlarm
_037FF640:
	mov	r0, #1
	strb	r0, [r5]
	add	sp, sp, #12
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FF654:	.word	_03808EEC
_037FF658:	.word	AlarmHandler

	arm_func_start SND_SetupAlarm
SND_SetupAlarm: ; 0x037FF65C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	ldr	r5, [sp, #24]
	ldr	r1, _037FF6B4	; =_03808EEC
	add	r4, r1, r0, lsl #6
	ldrb	r0, [r1, r0, lsl #6]
	cmp	r0, #0
	beq	_037FF694
	add	r0, r4, #20
	bl	OS_CancelAlarm
	mov	r0, #0
	strb	r0, [r4]
_037FF694:
	str	r8, [r4, #4]
	str	r7, [r4, #8]
	str	r6, [r4, #12]
	str	r5, [r4, #16]
	ldr	r0, [sp, #28]
	strb	r0, [r4, #1]
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FF6B4:	.word	_03808EEC

	arm_func_start SND_AlarmInit
SND_AlarmInit: ; 0x037FF6B8
	mov	r3, #0
	mov	r2, r3
	ldr	r1, _037FF6E0	; =SNDi_Work
_037FF6C4:
	add	r0, r1, r3, lsl #6
	strb	r2, [r0, #3968]	; 0xf80
	strb	r2, [r0, #3969]	; 0xf81
	add	r3, r3, #1
	cmp	r3, #8
	blt	_037FF6C4
	bx	lr
_037FF6E0:	.word	SNDi_Work
