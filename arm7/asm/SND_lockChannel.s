	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03807F44
_03807F44: ;0x03807F44
	.space 0x03807F48 - 0x03807F44

	.global _03807F48
_03807F48: ;0x03807F48
	.space 0x03807F4C - 0x03807F48

    .section .text

	arm_func_start SND_GetLockedChannel
SND_GetLockedChannel: ; 0x037FC964
	ands	r0, r0, #1
	ldrne	r0, _037FC97C	; =_03807F44
	ldrne	r0, [r0]
	ldreq	r0, _037FC980	; =_03807F48
	ldreq	r0, [r0]
	bx	lr
_037FC97C:	.word	_03807F44
_037FC980:	.word	_03807F48

	arm_func_start SND_UnlockChannel
SND_UnlockChannel: ; 0x037FC984
	ands	r1, r1, #1
	ldreq	r1, _037FC9B8	; =_03807F48
	ldreq	r2, [r1]
	mvneq	r0, r0
	andeq	r0, r2, r0
	streq	r0, [r1]
	bxeq	lr
	ldr	r1, _037FC9BC	; =_03807F44
	ldr	r2, [r1]
	mvn	r0, r0
	and	r0, r2, r0
	str	r0, [r1]
	bx	lr
_037FC9B8:	.word	_03807F48
_037FC9BC:	.word	_03807F44

	arm_func_start SND_LockChannel
SND_LockChannel: ; 0x037FC9C0
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r9, r1
	mov	r7, sl
	mov	r6, #0
	mov	fp, r6
	str	r6, [sp]
	mov	r4, r6
	mov	r5, #1
	b	_037FCA6C
_037FC9EC:
	ands	r0, r7, #1
	beq	_037FCA64
	mov	r1, #84	; 0x54
	ldr	r0, _037FCAAC	; =SNDi_Work
	mla	r8, r6, r1, r0
	ldr	r0, _037FCAB0	; =_03807F48
	ldr	r1, [r0]
	mov	r0, r5, lsl r6
	ands	r0, r1, r0
	bne	_037FCA64
	ldr	r3, [r8, #72]	; 0x48
	cmp	r3, #0
	beq	_037FCA34
	mov	r0, r8
	mov	r1, fp
	ldr	r2, [r8, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCA34:
	mov	r0, r6
	ldr	r1, [sp]
	bl	SND_StopChannel
	strb	r4, [r8, #34]	; 0x22
	mov	r0, r8
	bl	SND_FreeExChannel
	ldrb	r0, [r8, #3]
	bic	r0, r0, #248	; 0xf8
	strb	r0, [r8, #3]
	ldrb	r0, [r8, #3]
	bic	r0, r0, #1
	strb	r0, [r8, #3]
_037FCA64:
	add	r6, r6, #1
	mov	r7, r7, lsr #1
_037FCA6C:
	cmp	r6, #16
	bge	_037FCA7C
	cmp	r7, #0
	bne	_037FC9EC
_037FCA7C:
	ands	r0, r9, #1
	ldrne	r0, _037FCAB4	; =_03807F44
	ldrne	r1, [r0]
	orrne	r1, r1, sl
	strne	r1, [r0]
	ldreq	r0, _037FCAB0	; =_03807F48
	ldreq	r1, [r0]
	orreq	r1, r1, sl
	streq	r1, [r0]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FCAAC:	.word	SNDi_Work
_037FCAB0:	.word	_03807F48
_037FCAB4:	.word	_03807F44

	arm_func_start SND_StopUnlockedChannel
SND_StopUnlockedChannel: ; 0x037FCAB8
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	r8, #0
	mov	r6, r8
	mov	r5, r8
	mov	r4, r8
	ldr	fp, _037FCB78	; =SNDi_Work
	mov	r7, #1
	b	_037FCB5C
_037FCAE0:
	ands	r0, sl, #1
	beq	_037FCB54
	mov	r0, #84	; 0x54
	mla	r9, r8, r0, fp
	ldr	r0, _037FCB7C	; =_03807F48
	ldr	r1, [r0]
	mov	r0, r7, lsl r8
	ands	r0, r1, r0
	bne	_037FCB54
	ldr	r3, [r9, #72]	; 0x48
	cmp	r3, #0
	beq	_037FCB24
	mov	r0, r9
	mov	r1, r6
	ldr	r2, [r9, #76]	; 0x4c
	mov	lr, pc
	bx	r3
_037FCB24:
	mov	r0, r8
	mov	r1, r5
	bl	SND_StopChannel
	strb	r4, [r9, #34]	; 0x22
	mov	r0, r9
	bl	SND_FreeExChannel
	ldrb	r0, [r9, #3]
	bic	r0, r0, #248	; 0xf8
	strb	r0, [r9, #3]
	ldrb	r0, [r9, #3]
	bic	r0, r0, #1
	strb	r0, [r9, #3]
_037FCB54:
	add	r8, r8, #1
	mov	sl, sl, lsr #1
_037FCB5C:
	cmp	r8, #16
	bge	_037FCB6C
	cmp	sl, #0
	bne	_037FCAE0
_037FCB6C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FCB78:	.word	SNDi_Work
_037FCB7C:	.word	_03807F48
