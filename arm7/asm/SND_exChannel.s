	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SND_FreeExChannel
SND_FreeExChannel: ; 0x037FCB80
	cmp	r0, #0
	movne	r1, #0
	strne	r1, [r0, #72]	; 0x48
	strne	r1, [r0, #76]	; 0x4c
	bx	lr

	arm_func_start SND_AllocExChannel
SND_AllocExChannel: ; 0x037FCB94
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	fp, r3
	ldr	r0, _037FCCBC	; =_03807F48
	ldr	r0, [r0]
	mvn	r0, r0
	and	sl, sl, r0
	cmp	r2, #0
	ldreq	r0, _037FCCC0	; =_03807F44
	ldreq	r0, [r0]
	mvneq	r0, r0
	andeq	sl, sl, r0
	mov	r8, #0
	mov	r7, r8
	mov	r5, #1
	mov	r4, #84	; 0x54
_037FCBDC:
	ldr	r0, _037FCCC4	; =_03807298
	ldrb	r1, [r0, r7]
	mov	r0, r5, lsl r1
	ands	r0, sl, r0
	beq	_037FCC34
	ldr	r0, _037FCCC8	; =SNDi_Work
	mla	r6, r1, r4, r0
	cmp	r8, #0
	moveq	r8, r6
	beq	_037FCC34
	ldrb	r1, [r8, #34]	; 0x22
	ldrb	r0, [r6, #34]	; 0x22
	cmp	r0, r1
	bhi	_037FCC34
	cmp	r0, r1
	bne	_037FCC30
	mov	r0, r8
	mov	r1, r6
	bl	FUN_037FC63C
	cmp	r0, #0
	bge	_037FCC34
_037FCC30:
	mov	r8, r6
_037FCC34:
	add	r7, r7, #1
	cmp	r7, #16
	blt	_037FCBDC
	cmp	r8, #0
	moveq	r0, #0
	beq	_037FCCB0
	ldrb	r0, [r8, #34]	; 0x22
	cmp	r9, r0
	movlt	r0, #0
	blt	_037FCCB0
	ldr	r3, [r8, #72]	; 0x48
	cmp	r3, #0
	beq	_037FCC7C
	mov	r0, r8
	mov	r1, #0
	ldr	r2, [r8, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCC7C:
	ldrb	r0, [r8, #3]
	bic	r0, r0, #248	; 0xf8
	orr	r0, r0, #16
	strb	r0, [r8, #3]
	ldrb	r0, [r8, #3]
	bic	r0, r0, #1
	strb	r0, [r8, #3]
	mov	r0, r8
	mov	r1, fp
	ldr	r2, [sp, #40]	; 0x28
	mov	r3, r9
	bl	FUN_037FC6E8
	mov	r0, r8
_037FCCB0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FCCBC:	.word	_03807F48
_037FCCC0:	.word	_03807F44
_037FCCC4:	.word	_03807298
_037FCCC8:	.word	SNDi_Work

	arm_func_start SND_IsExChannelActive
SND_IsExChannelActive: ; 0x037FCCCC
	ldrb	r0, [r0, #3]
	mov	r0, r0, lsl #31
	mov	r0, r0, lsr #31
	bx	lr

	arm_func_start SND_ReleaseExChannel
SND_ReleaseExChannel: ; 0x037FCCDC
	mov	r1, #3
	strb	r1, [r0, #2]
	bx	lr

	arm_func_start SND_SetExChannelRelease
SND_SetExChannelRelease: ; 0x037FCCE8
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, r1
	bl	FUN_037FC794
	strh	r0, [r4, #32]
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_SetExChannelSustain
SND_SetExChannelSustain: ; 0x037FCD04
	strb	r1, [r0, #29]
	bx	lr

	arm_func_start SND_SetExChannelDecay
SND_SetExChannelDecay: ; 0x037FCD0C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, r1
	bl	FUN_037FC794
	strh	r0, [r4, #30]
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_SetExChannelAttack
SND_SetExChannelAttack: ; 0x037FCD28
	cmp	r1, #109	; 0x6d
	rsblt	r1, r1, #255	; 0xff
	strltb	r1, [r0, #28]
	rsbge	r2, r1, #127	; 0x7f
	ldrge	r1, _037FCD48	; =_038072A8
	ldrgeb	r1, [r1, r2]
	strgeb	r1, [r0, #28]
	bx	lr
_037FCD48:	.word	_038072A8

	arm_func_start SND_UpdateExChannelEnvelope
SND_UpdateExChannelEnvelope: ; 0x037FCD4C
	cmp	r1, #0
	beq	_037FCDF0
	ldrb	r1, [r0, #2]
	cmp	r1, #3
	addls	pc, pc, r1, lsl #2
	b	_037FCDF0
	b	_037FCD74
	b	_037FCDA4
	b	_037FCDF0
	b	_037FCDE0
_037FCD74:
	ldr	r1, [r0, #16]
	rsb	r2, r1, #0
	ldrb	r1, [r0, #28]
	mul	r1, r2, r1
	mov	r1, r1, asr #8
	rsb	r1, r1, #0
	str	r1, [r0, #16]
	ldr	r1, [r0, #16]
	cmp	r1, #0
	moveq	r1, #1
	streqb	r1, [r0, #2]
	b	_037FCDF0
_037FCDA4:
	ldrb	r1, [r0, #29]
	mov	r2, r1, lsl #1
	ldr	r1, _037FCDFC	; =SNDi_DecibelSquareTable
	ldrsh	r1, [r1, r2]
	mov	r3, r1, lsl #7
	ldr	r2, [r0, #16]
	ldrh	r1, [r0, #30]
	sub	r1, r2, r1
	str	r1, [r0, #16]
	ldr	r1, [r0, #16]
	cmp	r1, r3
	strle	r3, [r0, #16]
	movle	r1, #2
	strleb	r1, [r0, #2]
	b	_037FCDF0
_037FCDE0:
	ldr	r2, [r0, #16]
	ldrh	r1, [r0, #32]
	sub	r1, r2, r1
	str	r1, [r0, #16]
_037FCDF0:
	ldr	r0, [r0, #16]
	mov	r0, r0, asr #7
	bx	lr
_037FCDFC:	.word	SNDi_DecibelSquareTable

	arm_func_start SND_StartExChannelNoise
SND_StartExChannelNoise: ; 0x037FCE00
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldrb	r2, [r0]
	cmp	r2, #14
	movcc	r0, #0
	bcc	_037FCE3C
	cmp	r2, #15
	movhi	r0, #0
	bhi	_037FCE3C
	mov	r2, #2
	strb	r2, [r0, #1]
	ldr	r2, _037FCE48	; =0x00001F46
	strh	r2, [r0, #60]	; 0x3c
	bl	FUN_037FC69C
	mov	r0, #1
_037FCE3C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FCE48:	.word	0x00001F46

	arm_func_start SND_StartExChannelPsg
SND_StartExChannelPsg: ; 0x037FCE4C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldrb	r3, [r0]
	cmp	r3, #8
	movcc	r0, #0
	bcc	_037FCE90
	cmp	r3, #13
	movhi	r0, #0
	bhi	_037FCE90
	mov	r3, #1
	strb	r3, [r0, #1]
	str	r1, [r0, #68]	; 0x44
	ldr	r1, _037FCE9C	; =0x00001F46
	strh	r1, [r0, #60]	; 0x3c
	mov	r1, r2
	bl	FUN_037FC69C
	mov	r0, #1
_037FCE90:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FCE9C:	.word	0x00001F46

	arm_func_start SND_StartExChannelPcm
SND_StartExChannelPcm: ; 0x037FCEA0
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	lr, r2
	mov	r0, #0
	strb	r0, [r4, #1]
	add	ip, r4, #56	; 0x38
	ldmia	r1, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	str	lr, [r4, #68]	; 0x44
	mov	r0, r4
	mov	r1, r3
	bl	FUN_037FC69C
	mov	r0, #1
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_ExChannelMain
SND_ExChannelMain: ; 0x037FCEDC
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #28
	mov	r6, r0
	mov	r4, #0
	mov	fp, r4
	mov	r7, #1
	str	r4, [sp, #8]
	mov	r0, #127	; 0x7f
	str	r0, [sp, #20]
	str	r4, [sp, #16]
	str	r4, [sp, #12]
	str	r4, [sp, #4]
	str	r4, [sp]
_037FCF10:
	ldr	r8, [sp]
	mov	sl, r8
	mov	r9, r8
	mov	r1, #84	; 0x54
	ldr	r0, _037FD1E4	; =SNDi_Work
	mla	r5, r4, r1, r0
	ldrb	r1, [r5, #3]
	mov	r0, r1, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FD1CC
	mov	r0, r1, lsl #30
	movs	r0, r0, lsr #31
	beq	_037FCF74
	bic	r0, r1, #248	; 0xf8
	mov	r1, r1, lsl #24
	mov	r1, r1, lsr #27
	orr	r1, r1, #1
	and	r1, r1, #255	; 0xff
	and	r1, r1, #31
	orr	r0, r0, r1, lsl #3
	strb	r0, [r5, #3]
	ldrb	r0, [r5, #3]
	bic	r0, r0, #2
	strb	r0, [r5, #3]
	b	_037FCFC0
_037FCF74:
	mov	r0, r4
	bl	SND_IsChannelActive
	cmp	r0, #0
	bne	_037FCFC0
	ldr	r3, [r5, #72]	; 0x48
	cmp	r3, #0
	streqb	fp, [r5, #34]	; 0x22
	beq	_037FCFA8
	mov	r0, r5
	mov	r1, r7
	ldr	r2, [r5, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCFA8:
	ldr	r0, [sp, #4]
	strh	r0, [r5, #36]	; 0x24
	ldrb	r0, [r5, #3]
	bic	r0, r0, #1
	strb	r0, [r5, #3]
	b	_037FD1CC
_037FCFC0:
	ldrb	r0, [r5, #9]
	mov	r1, r0, lsl #1
	ldr	r0, _037FD1E8	; =SNDi_DecibelSquareTable
	ldrsh	r0, [r0, r1]
	add	r8, r8, r0
	ldrb	r1, [r5, #8]
	ldrb	r0, [r5, #5]
	sub	r0, r1, r0
	add	sl, sl, r0, lsl #6
	mov	r0, r5
	mov	r1, r6
	bl	SND_UpdateExChannelEnvelope
	add	r8, r8, r0
	mov	r0, r5
	mov	r1, r6
	bl	FUN_037FC5CC
	add	r2, sl, r0
	ldrsh	r0, [r5, #12]
	add	r1, r8, r0
	ldrsh	r0, [r5, #6]
	add	r8, r1, r0
	ldrsh	r0, [r5, #14]
	add	sl, r2, r0
	mov	r0, r5
	mov	r1, r6
	bl	FUN_037FC530
	ldrb	r1, [r5, #40]	; 0x28
	cmp	r1, #0
	beq	_037FD05C
	cmp	r1, #1
	beq	_037FD048
	cmp	r1, #2
	addeq	r9, r9, r0
	b	_037FD060
_037FD048:
	mov	r1, #32768	; 0x8000
	rsb	r1, r1, #0
	cmp	r8, r1
	addgt	r8, r8, r0
	b	_037FD060
_037FD05C:
	add	sl, sl, r0
_037FD060:
	ldrsb	r0, [r5, #10]
	add	r9, r9, r0
	ldrb	r0, [r5, #4]
	cmp	r0, #127	; 0x7f
	mulne	r0, r9, r0
	addne	r0, r0, #64	; 0x40
	movne	r9, r0, asr #7
	ldrsb	r0, [r5, #11]
	add	r9, r9, r0
	ldrb	r0, [r5, #2]
	cmp	r0, #3
	bne	_037FD0EC
	ldr	r0, _037FD1EC	; =0xFFFFFD2D
	cmp	r8, r0
	bgt	_037FD0EC
	ldrb	r0, [r5, #3]
	bic	r0, r0, #248	; 0xf8
	orr	r0, r0, #16
	strb	r0, [r5, #3]
	ldr	r3, [r5, #72]	; 0x48
	cmp	r3, #0
	ldreq	r0, [sp, #8]
	streqb	r0, [r5, #34]	; 0x22
	beq	_037FD0D4
	mov	r0, r5
	mov	r1, r7
	ldr	r2, [r5, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FD0D4:
	ldr	r0, [sp, #12]
	strh	r0, [r5, #36]	; 0x24
	ldrb	r0, [r5, #3]
	bic	r0, r0, #1
	strb	r0, [r5, #3]
	b	_037FD1CC
_037FD0EC:
	mov	r0, r8
	bl	SND_CalcChannelVolume
	mov	r8, r0
	ldrh	r0, [r5, #60]	; 0x3c
	mov	r1, sl
	bl	SND_CalcTimer
	ldrb	r1, [r5, #1]
	cmp	r1, #1
	ldreq	r1, _037FD1F0	; =0x0000FFFC
	andeq	r0, r0, r1
	moveq	r0, r0, lsl #16
	moveq	r0, r0, lsr #16
	adds	r9, r9, #64	; 0x40
	ldrmi	r9, [sp, #16]
	bmi	_037FD130
	cmp	r9, #127	; 0x7f
	ldrgt	r9, [sp, #20]
_037FD130:
	ldrh	r1, [r5, #36]	; 0x24
	cmp	r8, r1
	beq	_037FD164
	strh	r8, [r5, #36]	; 0x24
	ldrb	r2, [r5, #3]
	bic	r1, r2, #248	; 0xf8
	mov	r2, r2, lsl #24
	mov	r2, r2, lsr #27
	orr	r2, r2, #8
	and	r2, r2, #255	; 0xff
	and	r2, r2, #31
	orr	r1, r1, r2, lsl #3
	strb	r1, [r5, #3]
_037FD164:
	ldrh	r1, [r5, #38]	; 0x26
	cmp	r0, r1
	beq	_037FD198
	strh	r0, [r5, #38]	; 0x26
	ldrb	r0, [r5, #3]
	bic	r1, r0, #248	; 0xf8
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	orr	r0, r0, #4
	and	r0, r0, #255	; 0xff
	and	r0, r0, #31
	orr	r0, r1, r0, lsl #3
	strb	r0, [r5, #3]
_037FD198:
	ldrb	r0, [r5, #35]	; 0x23
	cmp	r9, r0
	beq	_037FD1CC
	strb	r9, [r5, #35]	; 0x23
	ldrb	r0, [r5, #3]
	bic	r1, r0, #248	; 0xf8
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	orr	r0, r0, #16
	and	r0, r0, #255	; 0xff
	and	r0, r0, #31
	orr	r0, r1, r0, lsl #3
	strb	r0, [r5, #3]
_037FD1CC:
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FCF10
	add	sp, sp, #28
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FD1E4:	.word	SNDi_Work
_037FD1E8:	.word	SNDi_DecibelSquareTable
_037FD1EC:	.word	0xFFFFFD2D
_037FD1F0:	.word	0x0000FFFC

	arm_func_start SND_UpdateExChannel
SND_UpdateExChannel: ; 0x037FD1F4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #24
	mov	r8, #0
	mov	r4, #2
	mov	r5, #1
	mov	r6, r8
	ldr	r7, _037FD3DC	; =SNDi_Work
	mov	sl, #84	; 0x54
_037FD214:
	mla	r9, r8, sl, r7
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	movs	r0, r0, lsr #27
	beq	_037FD374
	ands	r0, r0, #2
	beq	_037FD23C
	mov	r0, r8
	mov	r1, r6
	bl	SND_StopChannel
_037FD23C:
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	mov	r1, r0, lsr #27
	ands	r0, r1, #1
	beq	_037FD318
	ldrb	r0, [r9, #1]
	cmp	r0, #0
	beq	_037FD270
	cmp	r0, #1
	beq	_037FD2C8
	cmp	r0, #2
	beq	_037FD2F4
	b	_037FD374
_037FD270:
	ldrb	r0, [r9, #57]	; 0x39
	cmp	r0, #0
	movne	r3, r5
	moveq	r3, r4
	ldrh	r1, [r9, #36]	; 0x24
	ldrh	r0, [r9, #62]	; 0x3e
	str	r0, [sp]
	ldr	r0, [r9, #64]	; 0x40
	str	r0, [sp, #4]
	and	r0, r1, #255	; 0xff
	str	r0, [sp, #8]
	mov	r0, r1, asr #8
	str	r0, [sp, #12]
	ldrh	r0, [r9, #38]	; 0x26
	str	r0, [sp, #16]
	ldrb	r0, [r9, #35]	; 0x23
	str	r0, [sp, #20]
	mov	r0, r8
	ldr	r1, [r9, #68]	; 0x44
	ldrb	r2, [r9, #56]	; 0x38
	bl	SND_SetupChannelPcm
	b	_037FD374
_037FD2C8:
	ldrh	r3, [r9, #36]	; 0x24
	ldrh	r0, [r9, #38]	; 0x26
	str	r0, [sp]
	ldrb	r0, [r9, #35]	; 0x23
	str	r0, [sp, #4]
	mov	r0, r8
	ldr	r1, [r9, #68]	; 0x44
	and	r2, r3, #255	; 0xff
	mov	r3, r3, asr #8
	bl	SND_SetupChannelPsg
	b	_037FD374
_037FD2F4:
	ldrh	r2, [r9, #36]	; 0x24
	ldrb	r0, [r9, #35]	; 0x23
	str	r0, [sp]
	mov	r0, r8
	and	r1, r2, #255	; 0xff
	mov	r2, r2, asr #8
	ldrh	r3, [r9, #38]	; 0x26
	bl	SND_SetupChannelNoise
	b	_037FD374
_037FD318:
	ands	r0, r1, #4
	beq	_037FD32C
	mov	r0, r8
	ldrh	r1, [r9, #38]	; 0x26
	bl	SND_SetChannelTimer
_037FD32C:
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	ands	r0, r0, #8
	beq	_037FD354
	ldrh	r2, [r9, #36]	; 0x24
	mov	r0, r8
	and	r1, r2, #255	; 0xff
	mov	r2, r2, asr #8
	bl	SND_SetChannelVolume
_037FD354:
	ldrb	r0, [r9, #3]
	mov	r0, r0, lsl #24
	mov	r0, r0, lsr #27
	ands	r0, r0, #16
	beq	_037FD374
	mov	r0, r8
	ldrb	r1, [r9, #35]	; 0x23
	bl	SND_SetChannelPan
_037FD374:
	add	r8, r8, #1
	cmp	r8, #16
	blt	_037FD214
	mov	r5, #0
	ldr	r3, _037FD3DC	; =SNDi_Work
	mov	r1, #84	; 0x54
_037FD38C:
	mla	r4, r5, r1, r3
	ldrb	r0, [r4, #3]
	mov	r0, r0, lsl #24
	movs	r0, r0, lsr #27
	beq	_037FD3C4
	ands	r0, r0, #1
	movne	r0, r5, lsl #4
	addne	r0, r0, #67108864	; 0x4000000
	ldrneb	r2, [r0, #1027]	; 0x403
	orrne	r2, r2, #128	; 0x80
	strneb	r2, [r0, #1027]	; 0x403
	ldrb	r0, [r4, #3]
	bic	r0, r0, #248	; 0xf8
	strb	r0, [r4, #3]
_037FD3C4:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FD38C
	add	sp, sp, #24
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_037FD3DC:	.word	SNDi_Work

	arm_func_start SND_ExChannelInit
SND_ExChannelInit: ; 0x037FD3E0
	mov	ip, #0
	ldr	r2, _037FD434	; =SNDi_Work
	mov	r0, #84	; 0x54
_037FD3EC:
	mul	r1, ip, r0
	add	r3, r2, r1
	strb	ip, [r2, r1]
	ldrb	r1, [r3, #3]
	bic	r1, r1, #248	; 0xf8
	strb	r1, [r3, #3]
	ldrb	r1, [r3, #3]
	bic	r1, r1, #1
	strb	r1, [r3, #3]
	add	ip, ip, #1
	cmp	ip, #16
	blt	_037FD3EC
	mov	r1, #0
	ldr	r0, _037FD438	; =_03807F48
	str	r1, [r0]
	ldr	r0, _037FD43C	; =_03807F44
	str	r1, [r0]
	bx	lr
_037FD434:	.word	SNDi_Work
_037FD438:	.word	_03807F48
_037FD43C:	.word	_03807F44
