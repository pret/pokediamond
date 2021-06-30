	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start ExChannelLfoUpdate
ExChannelLfoUpdate: ; 0x037FC530
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, r1
	add	r0, r6, #40	; 0x28
	bl	SND_GetLfoValue
	mov	r4, r0
	mov	ip, r0, asr #31
	mov	r3, #0
	cmp	ip, r3
	cmpeq	r0, r3
	beq	_037FC5B0
	ldrb	r1, [r6, #40]	; 0x28
	cmp	r1, #0
	beq	_037FC59C
	cmp	r1, #1
	beq	_037FC584
	cmp	r1, #2
	moveq	ip, ip, lsl #6
	orreq	ip, ip, r0, lsr #26
	moveq	r4, r0, lsl #6
	b	_037FC5A8
_037FC584:
	mov	r2, #60	; 0x3c
	umull	r4, r1, r0, r2
	mla	r1, r0, r3, r1
	mla	r1, ip, r2, r1
	mov	ip, r1
	b	_037FC5A8
_037FC59C:
	mov	ip, ip, lsl #6
	orr	ip, ip, r0, lsr #26
	mov	r4, r0, lsl #6
_037FC5A8:
	mov	r4, r4, lsr #14
	orr	r4, r4, ip, lsl #18
_037FC5B0:
	cmp	r5, #0
	beq	_037FC5C0
	add	r0, r6, #40	; 0x28
	bl	SND_UpdateLfo
_037FC5C0:
	mov	r0, r4
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start ExChannelSweepUpdate
ExChannelSweepUpdate: ; 0x037FC5CC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r5, r1
	ldrsh	r3, [r4, #50]	; 0x32
	cmp	r3, #0
	moveq	r0, #0
	beq	_037FC630
	ldr	r0, [r4, #20]
	ldr	r2, [r4, #24]
	cmp	r0, r2
	movge	r0, #0
	bge	_037FC630
	sub	r0, r2, r0
	smull	r0, r1, r3, r0
	mov	r3, r2, asr #31
	bl	_ll_sdiv
	cmp	r5, #0
	beq	_037FC630
	ldrb	r1, [r4, #3]
	mov	r1, r1, lsl #29
	movs	r1, r1, lsr #31
	ldrne	r1, [r4, #20]
	addne	r1, r1, #1
	strne	r1, [r4, #20]
_037FC630:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start ExChannelVolumeCmp
ExChannelVolumeCmp: ; 0x037FC63C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldrh	lr, [r0, #36]	; 0x24
	and	r2, lr, #255	; 0xff
	ldrh	ip, [r1, #36]	; 0x24
	and	r0, ip, #255	; 0xff
	mov	r2, r2, lsl #4
	mov	r3, r0, lsl #4
	ldr	r1, _037FC698	; =sSampleDataShiftTable
	ldrb	r0, [r1, lr, asr #8]
	mov	r2, r2, asr r0
	ldrb	r0, [r1, ip, asr #8]
	mov	r0, r3, asr r0
	cmp	r2, r0
	beq	_037FC688
	cmp	r2, r0
	movlt	r0, #1
	mvnge	r0, #0
	b	_037FC68C
_037FC688:
	mov	r0, #0
_037FC68C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC698:	.word	sSampleDataShiftTable

	arm_func_start ExChannelStart
ExChannelStart: ; 0x037FC69C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FC6E4	; =0xFFFE9680
	str	r0, [r4, #16]
	mov	r0, #0
	strb	r0, [r4, #2]
	str	r1, [r4, #52]	; 0x34
	add	r0, r4, #40	; 0x28
	bl	SND_StartLfo
	ldrb	r0, [r4, #3]
	orr	r0, r0, #2
	strb	r0, [r4, #3]
	ldrb	r0, [r4, #3]
	bic	r0, r0, #1
	orr	r0, r0, #1
	strb	r0, [r4, #3]
	ldmia	sp!, {r4, lr}
	bx	lr
_037FC6E4:	.word	0xFFFE9680

	arm_func_start ExChannelSetup
ExChannelSetup: ; 0x037FC6E8
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	ip, #0
	str	ip, [r4, #80]	; 0x50
	str	r1, [r4, #72]	; 0x48
	str	r2, [r4, #76]	; 0x4c
	str	ip, [r4, #52]	; 0x34
	strb	r3, [r4, #34]	; 0x22
	mov	r1, #127	; 0x7f
	strh	r1, [r4, #36]	; 0x24
	ldrb	r2, [r4, #3]
	bic	r2, r2, #2
	strb	r2, [r4, #3]
	ldrb	r2, [r4, #3]
	orr	r2, r2, #4
	strb	r2, [r4, #3]
	mov	r2, #60	; 0x3c
	strb	r2, [r4, #8]
	strb	r2, [r4, #5]
	strb	r1, [r4, #9]
	strb	ip, [r4, #10]
	strh	ip, [r4, #12]
	strh	ip, [r4, #6]
	strh	ip, [r4, #14]
	strb	ip, [r4, #11]
	strb	r1, [r4, #4]
	strh	ip, [r4, #50]	; 0x32
	str	ip, [r4, #24]
	str	ip, [r4, #20]
	bl	SND_SetExChannelAttack
	mov	r0, r4
	mov	r1, #127	; 0x7f
	bl	SND_SetExChannelDecay
	mov	r0, r4
	mov	r1, #127	; 0x7f
	bl	SND_SetExChannelSustain
	mov	r0, r4
	mov	r1, #127	; 0x7f
	bl	SND_SetExChannelRelease
	add	r0, r4, #40	; 0x28
	bl	SND_InitLfoParam
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start CalcDecayCoeff
CalcDecayCoeff: ; 0x037FC794
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r1, r0
	cmp	r1, #127	; 0x7f
	ldreq	r0, _037FC7F0	; =0x0000FFFF
	beq	_037FC7E4
	cmp	r1, #126	; 0x7e
	moveq	r0, #15360	; 0x3c00
	beq	_037FC7E4
	cmp	r1, #50	; 0x32
	movlt	r0, r1, lsl #1
	addlt	r0, r0, #1
	movlt	r0, r0, lsl #16
	movlt	r0, r0, lsr #16
	blt	_037FC7E4
	mov	r0, #7680	; 0x1e00
	rsb	r1, r1, #126	; 0x7e
	bl	_s32_div_f
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
_037FC7E4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FC7F0:	.word	0x0000FFFF
