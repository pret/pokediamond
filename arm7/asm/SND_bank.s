	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start GetWaveData
GetWaveData: ; 0x037FF114
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	add	r0, r0, r1, lsl #3
	ldr	r0, [r0, #24]
	cmp	r0, #0
	moveq	r0, #0
	beq	_037FF148
	ldr	r1, [r0, #56]	; 0x38
	cmp	r2, r1
	movcs	r0, #0
	bcs	_037FF148
	mov	r1, r2
	bl	SND_GetWaveDataAddress
_037FF148:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start SND_NoteOn
SND_NoteOn: ; 0x037FF154
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, r0
	mov	r8, r1
	mov	r7, r2
	mov	r6, r3
	ldr	r5, [sp, #36]	; 0x24
	ldrb	r4, [r5, #10]
	cmp	r4, #255	; 0xff
	mvneq	r6, #0
	moveq	r4, #0
	ldrb	r0, [r5]
	cmp	r0, #4
	addls	pc, pc, r0, lsl #2
	b	_037FF210
	b	_037FF210
	b	_037FF1A4
	b	_037FF1EC
	b	_037FF200
	b	_037FF1A4
_037FF1A4:
	cmp	r0, #1
	ldrneh	r1, [r5, #4]
	ldrneh	r0, [r5, #2]
	orrne	r1, r0, r1, lsl #16
	bne	_037FF1CC
	ldr	r0, [sp, #32]
	ldrh	r1, [r5, #4]
	ldrh	r2, [r5, #2]
	bl	GetWaveData
	mov	r1, r0
_037FF1CC:
	cmp	r1, #0
	moveq	r0, #0
	beq	_037FF214
	mov	r0, r9
	add	r2, r1, #12
	mov	r3, r6
	bl	SND_StartExChannelPcm
	b	_037FF214
_037FF1EC:
	mov	r0, r9
	ldrh	r1, [r5, #2]
	mov	r2, r6
	bl	SND_StartExChannelPsg
	b	_037FF214
_037FF200:
	mov	r0, r9
	mov	r1, r6
	bl	SND_StartExChannelNoise
	b	_037FF214
_037FF210:
	mov	r0, #0
_037FF214:
	cmp	r0, #0
	moveq	r0, #0
	beq	_037FF270
	strb	r8, [r9, #8]
	ldrb	r0, [r5, #6]
	strb	r0, [r9, #5]
	strb	r7, [r9, #9]
	mov	r0, r9
	ldrb	r1, [r5, #7]
	bl	SND_SetExChannelAttack
	mov	r0, r9
	ldrb	r1, [r5, #8]
	bl	SND_SetExChannelDecay
	mov	r0, r9
	ldrb	r1, [r5, #9]
	bl	SND_SetExChannelSustain
	mov	r0, r9
	mov	r1, r4
	bl	SND_SetExChannelRelease
	ldrb	r0, [r5, #11]
	sub	r0, r0, #64	; 0x40
	strb	r0, [r9, #10]
	mov	r0, #1
_037FF270:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr

	arm_func_start SND_GetWaveDataAddress
SND_GetWaveDataAddress: ; 0x037FF27C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	bl	SNDi_LockMutex
	add	r0, r5, r4, lsl #2
	ldr	r4, [r0, #60]	; 0x3c
	cmp	r4, #0
	beq	_037FF2AC
	cmp	r4, #33554432	; 0x2000000
	addcc	r4, r5, r4
	b	_037FF2B0
_037FF2AC:
	mov	r4, #0
_037FF2B0:
	bl	SNDi_UnlockMutex
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start SND_ReadInstData
SND_ReadInstData: ; 0x037FF2C4
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	movs	r7, r1
	mov	r5, r2
	mov	r4, r3
	movmi	r0, #0
	bmi	_037FF43C
	bl	SNDi_LockMutex
	ldr	r0, [r6, #56]	; 0x38
	cmp	r7, r0
	bcc	_037FF300
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF300:
	add	r0, r6, r7, lsl #2
	ldr	r3, [r0, #60]	; 0x3c
	strb	r3, [r4]
	ldrb	r0, [r4]
	cmp	r0, #17
	addls	pc, pc, r0, lsl #2
	b	_037FF428
	b	_037FF428
	b	_037FF364
	b	_037FF364
	b	_037FF364
	b	_037FF364
	b	_037FF364
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF428
	b	_037FF384
	b	_037FF3D4
_037FF364:
	add	r3, r6, r3, lsr #8
	add	r2, r4, #2
	mov	r1, #5
_037FF370:
	ldrh	r0, [r3], #2
	strh	r0, [r2], #2
	subs	r1, r1, #1
	bne	_037FF370
	b	_037FF434
_037FF384:
	add	r2, r6, r3, lsr #8
	ldrb	r1, [r2, #1]
	ldrb	r0, [r6, r3, lsr #8]
	cmp	r5, r0
	blt	_037FF3A0
	cmp	r5, r1
	ble	_037FF3AC
_037FF3A0:
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF3AC:
	sub	r1, r5, r0
	mov	r0, #12
	mla	r0, r1, r0, r2
	add	r2, r0, #2
	mov	r1, #6
_037FF3C0:
	ldrh	r0, [r2], #2
	strh	r0, [r4], #2
	subs	r1, r1, #1
	bne	_037FF3C0
	b	_037FF434
_037FF3D4:
	mov	r2, #0
	add	r1, r6, r3, lsr #8
	b	_037FF3F8
_037FF3E0:
	add	r2, r2, #1
	cmp	r2, #8
	blt	_037FF3F8
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF3F8:
	ldrb	r0, [r1, r2]
	cmp	r5, r0
	bgt	_037FF3E0
	mov	r0, #12
	mla	r0, r2, r0, r1
	add	r2, r0, #8
	mov	r1, #6
_037FF414:
	ldrh	r0, [r2], #2
	strh	r0, [r4], #2
	subs	r1, r1, #1
	bne	_037FF414
	b	_037FF434
_037FF428:
	bl	SNDi_UnlockMutex
	mov	r0, #0
	b	_037FF43C
_037FF434:
	bl	SNDi_UnlockMutex
	mov	r0, #1
_037FF43C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
