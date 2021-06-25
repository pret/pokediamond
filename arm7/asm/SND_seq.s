	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SNDi_SetTrackParam
SNDi_SetTrackParam: ; 0x037FE9F4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r1
	mov	r9, r2
	mov	r8, r3
	ldr	r7, [sp, #40]	; 0x28
	ldr	r2, _037FEA94	; =_038084AC
	mov	r1, #36	; 0x24
	mla	fp, r0, r1, r2
	mov	r6, #0
	mov	r0, r8, lsl #16
	mov	r4, r0, lsr #16
	and	r5, r8, #255	; 0xff
	b	_037FEA78
_037FEA2C:
	ands	r0, sl, #1
	beq	_037FEA70
	mov	r0, fp
	mov	r1, r6
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FEA70
	cmp	r7, #1
	beq	_037FEA64
	cmp	r7, #2
	beq	_037FEA6C
	cmp	r7, #4
	streq	r8, [r0, r9]
	b	_037FEA70
_037FEA64:
	strb	r5, [r0, r9]
	b	_037FEA70
_037FEA6C:
	strh	r4, [r0, r9]
_037FEA70:
	add	r6, r6, #1
	mov	sl, sl, lsr #1
_037FEA78:
	cmp	r6, #16
	bge	_037FEA88
	cmp	sl, #0
	bne	_037FEA2C
_037FEA88:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FEA94:	.word	(SNDi_Work + 0x540)

	arm_func_start SNDi_SetPlayerParam
SNDi_SetPlayerParam: ; 0x037FEA98
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	lr, _037FEAE0	; =_038084AC
	mov	ip, #36	; 0x24
	mla	ip, r0, ip, lr
	cmp	r3, #1
	beq	_037FEAC8
	cmp	r3, #2
	beq	_037FEAD0
	cmp	r3, #4
	streq	r2, [ip, r1]
	b	_037FEAD4
_037FEAC8:
	strb	r2, [ip, r1]
	b	_037FEAD4
_037FEAD0:
	strh	r2, [ip, r1]
_037FEAD4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FEAE0:	.word	(SNDi_Work + 0x540)

	arm_func_start SND_InvalidateBank
SND_InvalidateBank: ; 0x037FEAE4
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r6, r1
	mov	r5, #0
	ldr	r4, _037FEB40	; =_038084AC
	mov	r8, #36	; 0x24
_037FEAFC:
	mul	r1, r5, r8
	add	r0, r4, r1
	ldrb	r1, [r4, r1]
	mov	r1, r1, lsl #31
	movs	r1, r1, lsr #31
	beq	_037FEB2C
	ldr	r1, [r0, #32]
	cmp	r7, r1
	bhi	_037FEB2C
	cmp	r1, r6
	bhi	_037FEB2C
	bl	FUN_037FE3AC
_037FEB2C:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FEAFC
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FEB40:	.word	(SNDi_Work + 0x540)

	arm_func_start SND_InvalidateSeq
SND_InvalidateSeq: ; 0x037FEB44
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r7, #0
	mov	r5, r7
	ldr	fp, _037FEBDC	; =_038084AC
	mov	r4, #36	; 0x24
_037FEB64:
	mul	r0, r7, r4
	add	r8, fp, r0
	ldrb	r0, [fp, r0]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FEBC4
	mov	r6, r5
	b	_037FEBBC
_037FEB84:
	mov	r0, r8
	mov	r1, r6
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FEBB8
	ldr	r0, [r0, #40]	; 0x28
	cmp	sl, r0
	bhi	_037FEBB8
	cmp	r0, r9
	bhi	_037FEBB8
	mov	r0, r8
	bl	FUN_037FE3AC
	b	_037FEBC4
_037FEBB8:
	add	r6, r6, #1
_037FEBBC:
	cmp	r6, #16
	blt	_037FEB84
_037FEBC4:
	add	r7, r7, #1
	cmp	r7, #16
	blt	_037FEB64
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FEBDC:	.word	(SNDi_Work + 0x540)

	arm_func_start SND_SetTrackAllocatableChannel
SND_SetTrackAllocatableChannel: ; 0x037FEBE0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r1
	ldr	r3, _037FEC54	; =_038084AC
	mov	r1, #36	; 0x24
	mla	r5, r0, r1, r3
	mov	r4, #0
	mov	r0, r2, lsl #16
	mov	r7, r0, lsr #16
	b	_037FEC38
_037FEC08:
	ands	r0, r6, #1
	beq	_037FEC30
	mov	r0, r5
	mov	r1, r4
	bl	FUN_037FE460
	cmp	r0, #0
	strneh	r7, [r0, #30]
	ldrneb	r1, [r0]
	orrne	r1, r1, #128	; 0x80
	strneb	r1, [r0]
_037FEC30:
	add	r4, r4, #1
	mov	r6, r6, lsr #1
_037FEC38:
	cmp	r4, #16
	bge	_037FEC48
	cmp	r6, #0
	bne	_037FEC08
_037FEC48:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FEC54:	.word	(SNDi_Work + 0x540)

	arm_func_start SND_SetTrackMute
SND_SetTrackMute: ; 0x037FEC58
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r1
	mov	r6, r2
	ldr	r2, _037FECC8	; =_038084AC
	mov	r1, #36	; 0x24
	mla	r5, r0, r1, r2
	mov	r4, #0
	b	_037FECAC
_037FEC7C:
	ands	r0, r7, #1
	beq	_037FECA4
	mov	r0, r5
	mov	r1, r4
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FECA4
	mov	r1, r5
	mov	r2, r6
	bl	FUN_037FD440
_037FECA4:
	add	r4, r4, #1
	mov	r7, r7, lsr #1
_037FECAC:
	cmp	r4, #16
	bge	_037FECBC
	cmp	r7, #0
	bne	_037FEC7C
_037FECBC:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FECC8:	.word	(SNDi_Work + 0x540)

	arm_func_start SND_SkipSeq
SND_SkipSeq: ; 0x037FECCC
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r1
	ldr	r2, _037FED90	; =_038084AC
	mov	r1, #36	; 0x24
	mla	r5, r0, r1, r2
	mov	r8, #0
	mov	r4, #127	; 0x7f
_037FECE8:
	mov	r0, r5
	mov	r1, r8
	bl	FUN_037FE460
	movs	r7, r0
	beq	_037FED10
	mov	r1, r5
	mov	r2, r4
	bl	FUN_037FE588
	mov	r0, r7
	bl	FUN_037FE54C
_037FED10:
	add	r8, r8, #1
	cmp	r8, #16
	blt	_037FECE8
	bl	SND_StopIntervalTimer
	mov	r4, #0
	mov	r7, r4
	b	_037FED50
_037FED2C:
	mov	r0, r5
	mov	r1, r7
	bl	FUN_037FD548
	cmp	r0, #0
	beq	_037FED4C
	mov	r0, r5
	bl	FUN_037FE3AC
	b	_037FED58
_037FED4C:
	add	r4, r4, #1
_037FED50:
	cmp	r4, r6
	bcc	_037FED2C
_037FED58:
	bl	SND_StartIntervalTimer
	ldr	r0, _037FED94	; =SNDi_SharedWork
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FED88
	add	r3, r0, #64	; 0x40
	ldrb	r1, [r5, #1]
	mov	r0, #36	; 0x24
	mul	r2, r1, r0
	ldr	r0, [r3, r2]
	add	r0, r0, r4
	str	r0, [r3, r2]
_037FED88:
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FED90:	.word	(SNDi_Work + 0x540)
_037FED94:	.word	SNDi_SharedWork

	arm_func_start SND_PauseSeq
SND_PauseSeq: ; 0x037FED98
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	ldr	r5, _037FEE18	; =_038084AC
	mov	r2, #36	; 0x24
	mul	r3, r0, r2
	add	r4, r5, r3
	ldrb	r0, [r5, r3]
	bic	r2, r0, #4
	and	r0, r1, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r2, r0, lsl #2
	strb	r0, [r5, r3]
	cmp	r1, #0
	beq	_037FEE0C
	mov	r7, #0
	mov	r5, #127	; 0x7f
_037FEDD8:
	mov	r0, r4
	mov	r1, r7
	bl	FUN_037FE460
	movs	r6, r0
	beq	_037FEE00
	mov	r1, r4
	mov	r2, r5
	bl	FUN_037FE588
	mov	r0, r6
	bl	FUN_037FE54C
_037FEE00:
	add	r7, r7, #1
	cmp	r7, #16
	blt	_037FEDD8
_037FEE0C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FEE18:	.word	(SNDi_Work + 0x540)

	arm_func_start SND_StopSeq
SND_StopSeq: ; 0x037FEE1C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r2, _037FEE70	; =_038084AC
	mov	r0, #36	; 0x24
	mul	r1, r4, r0
	add	r0, r2, r1
	ldrb	r1, [r2, r1]
	mov	r1, r1, lsl #31
	movs	r1, r1, lsr #31
	beq	_037FEE68
	bl	FUN_037FE3AC
	ldr	r0, _037FEE74	; =SNDi_SharedWork
	ldr	r2, [r0]
	cmp	r2, #0
	ldrne	r1, [r2, #4]
	movne	r0, #1
	mvnne	r0, r0, lsl r4
	andne	r0, r1, r0
	strne	r0, [r2, #4]
_037FEE68:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FEE70:	.word	(SNDi_Work + 0x540)
_037FEE74:	.word	SNDi_SharedWork

	arm_func_start SND_StartSeq
SND_StartSeq: ; 0x037FEE78
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	SND_PrepareSeq
	mov	r0, r4
	bl	SND_StartPreparedSeq
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_StartPreparedSeq
SND_StartPreparedSeq: ; 0x037FEE94
	ldr	r2, _037FEEB0	; =_038084AC
	mov	r1, #36	; 0x24
	mul	r1, r0, r1
	ldrb	r0, [r2, r1]
	orr	r0, r0, #2
	strb	r0, [r2, r1]
	bx	lr
_037FEEB0:	.word	(SNDi_Work + 0x540)

	arm_func_start SND_PrepareSeq
SND_PrepareSeq: ; 0x037FEEB4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r8, r1
	mov	r6, r2
	mov	r5, r3
	ldr	r1, _037FEFFC	; =_038084AC
	mov	r0, #36	; 0x24
	mul	r0, r4, r0
	add	r7, r1, r0
	ldrb	r0, [r1, r0]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FEEF4
	mov	r0, r7
	bl	FUN_037FE3AC
_037FEEF4:
	mov	r0, r7
	mov	r1, r5
	bl	FUN_037FE5F8
	bl	FUN_037FD4C0
	movs	r9, r0
	bmi	_037FEFF0
	ldr	r0, _037FF000	; =_038086EC
	add	r5, r0, r9, lsl #6
	mov	r0, r5
	bl	FUN_037FE6BC
	mov	r0, r5
	mov	r1, r8
	mov	r2, r6
	bl	FUN_037FE6A8
	strb	r9, [r7, #8]
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE9B8
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE968
	add	r2, r5, #40	; 0x28
	ldr	r1, [r5, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r5, #40]	; 0x28
	cmp	r0, #254	; 0xfe
	ldrne	r0, [r2]
	subne	r0, r0, #1
	strne	r0, [r2]
	bne	_037FEFB8
	mov	r0, r5
	bl	FUN_037FE918
	mov	r0, r0, lsl #15
	mov	r5, r0, lsr #16
	mov	r6, #1
	ldr	r8, _037FF000	; =_038086EC
	b	_037FEFB0
_037FEF80:
	ands	r0, r5, #1
	beq	_037FEFA4
	bl	FUN_037FD4C0
	movs	r9, r0
	bmi	_037FEFB8
	add	r0, r8, r9, lsl #6
	bl	FUN_037FE6BC
	add	r0, r7, r6
	strb	r9, [r0, #8]
_037FEFA4:
	add	r6, r6, #1
	mov	r0, r5, lsl #15
	mov	r5, r0, lsr #16
_037FEFB0:
	cmp	r5, #0
	bne	_037FEF80
_037FEFB8:
	ldrb	r0, [r7]
	bic	r0, r0, #1
	orr	r0, r0, #1
	strb	r0, [r7]
	ldrb	r0, [r7]
	bic	r0, r0, #2
	strb	r0, [r7]
	ldr	r0, _037FF004	; =SNDi_SharedWork
	ldr	r2, [r0]
	cmp	r2, #0
	ldrne	r1, [r2, #4]
	movne	r0, #1
	orrne	r0, r1, r0, lsl r4
	strne	r0, [r2, #4]
_037FEFF0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FEFFC:	.word	(SNDi_Work + 0x540)
_037FF000:	.word	(SNDi_Work + 0x780)
_037FF004:	.word	SNDi_SharedWork

	arm_func_start SND_SeqMain
SND_SeqMain: ; 0x037FF008
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	mov	r8, r0
	mov	r5, #0
	mov	r6, r5
	mov	sl, #1
	ldr	r4, _037FF0A0	; =_038084AC
	mov	r9, #36	; 0x24
_037FF024:
	mul	r0, r6, r9
	add	r7, r4, r0
	ldrb	r1, [r4, r0]
	mov	r0, r1, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FF07C
	mov	r0, r1, lsl #30
	movs	r0, r0, lsr #31
	beq	_037FF06C
	cmp	r8, #0
	beq	_037FF064
	mov	r0, r1, lsl #29
	movs	r0, r0, lsr #31
	bne	_037FF064
	mov	r0, r7
	bl	FUN_037FE48C
_037FF064:
	mov	r0, r7
	bl	FUN_037FE1A0
_037FF06C:
	ldrb	r0, [r7]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	orrne	r5, r5, sl, lsl r6
_037FF07C:
	add	r6, r6, #1
	cmp	r6, #16
	blt	_037FF024
	ldr	r0, _037FF0A4	; =SNDi_SharedWork
	ldr	r0, [r0]
	cmp	r0, #0
	strne	r5, [r0, #4]
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_037FF0A0:	.word	(SNDi_Work + 0x540)
_037FF0A4:	.word	SNDi_SharedWork

	arm_func_start SND_SeqInit
SND_SeqInit: ; 0x037FF0A8
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	lr, #0
	ldr	r3, _037FF10C	; =_038084AC
	mov	r0, #36	; 0x24
_037FF0BC:
	mul	r2, lr, r0
	add	ip, r3, r2
	ldrb	r1, [r3, r2]
	bic	r1, r1, #1
	strb	r1, [r3, r2]
	strb	lr, [ip, #1]
	add	lr, lr, #1
	cmp	lr, #16
	blt	_037FF0BC
	mov	r2, #0
	ldr	r1, _037FF110	; =_038086EC
_037FF0E8:
	ldrb	r0, [r1, r2, lsl #6]
	bic	r0, r0, #1
	strb	r0, [r1, r2, lsl #6]
	add	r2, r2, #1
	cmp	r2, #32
	blt	_037FF0E8
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FF10C:	.word	(SNDi_Work + 0x540)
_037FF110:	.word	(SNDi_Work + 0x780)
