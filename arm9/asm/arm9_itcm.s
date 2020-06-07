	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	; MI
	arm_func_start MIi_DmaSetParams_wait_noInt
MIi_DmaSetParams_wait_noInt: ; 0x01FF84E4
	stmdb sp!,	{r4, lr}
	mov	ip, #12
	mul	r4, r0, ip
	add	ip, r4, #67108864	; 0x4000000
	ldr	lr, [pc, #64]	; 0x10b4dc
	str	r1, [ip, #176]	; 0xb0
	add	r4, r4, lr
	str	r2, [r4, #4]
	str	r3, [r4, #8]
	ldr	r1, [lr]
	cmp	r0, #0
	ldr	r0, [lr]
	moveq	r1, #0
	streq	r1, [r4]
	streq	r1, [r4, #4]
	ldreq	r0, _01FF8540
	ldr	r1, _01FF853C
	streq	r0, [r4, #8]
	ldr	r0, [r1]
	ldr	r0, [r1]
	ldmia sp!,	{r4, lr}
	bx	lr
_01FF853C:	.word 0x040000B0
_01FF8540:	.word 0x81400001

	arm_func_start MIi_DmaSetParams_noInt
MIi_DmaSetParams_noInt: ; 01FF8544
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	ip, #12
	mul	lr, r0, ip
	ldr	r0, _01FF8578
	add	ip, lr, #67108864	; 0x4000000
	str	r1, [ip, #176]	; 0xb0
	add	r0, lr, r0
	str	r2, [r0, #4]
	str	r3, [r0, #8]
	add	sp, sp, #4
	ldmfd	sp!, {lr}
	bx	lr
_01FF8578:	.word 0x040000B0

	arm_func_start MIi_DmaSetParams_wait
MIi_DmaSetParams_wait: ; 01FF857C
	stmdb sp!,	{r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r4, r3
	bl	OS_DisableInterrupts
	mov	r1, #12
	mul	r3, r7, r1
	add	r1, r3, #67108864	; 0x4000000
	ldr	r2, _01FF85E8
	str	r6, [r1, #176]	; 0xb0
	add	r3, r3, r2
	str	r5, [r3, #4]
	str	r4, [r3, #8]
	ldr	r1, [r2]
	cmp	r7, #0
	ldr	r1, [r2]
	moveq	r2, #0
	streq	r2, [r3]
	ldreq	r1, _01FF85EC
	streq	r2, [r3, #4]
	streq	r1, [r3, #8]
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, lr}
	bx	lr
_01FF85E8:	.word 0x040000B0
_01FF85EC:	.word 0x81400001

	arm_func_start MIi_DmaSetParams
MIi_DmaSetParams: ; 01FF85F0
	stmdb sp!,	{r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	mov	r4, r3
	bl	OS_DisableInterrupts
	mov	r1, #12
	mul	r3, r7, r1
	ldr	r1, _01FF863C
	add	r2, r3, #67108864	; 0x4000000
	str	r6, [r2, #176]	; 0xb0
	add	r1, r3, r1
	str	r5, [r1, #4]
	str	r4, [r1, #8]
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, lr}
	bx	lr
_01FF863C:	.word 0x040000B0

	arm_func_start MI_SendGXCommand
MI_SendGXCommand: ; 0x01FF8640
	stmdb sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	movs	r8, r2
	mov	sl, r0
	mov	r9, r1
	addeq	sp, sp, #4
	ldmeqia sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bxeq	lr
	mov	r3, #0
	bl	MIi_CheckDma0SourceAddress
	mov	r0, #3
	mul	r1, sl, r0
	ldr	r0, [pc, #104]	; 0x10b680
	add	r1, r1, #2
	add	r7, r0, r1, lsl #2
_01FF867C:
	ldr	r0, [r7]
	ands	r0, r0, #-2147483648	; 0x80000000
	bne	_01FF867C
	cmp	r8, #0
	beq	_01FF86C8
	ldr	fp, [pc, #76]	; 0x10b684
	mov	r5, #472	; 0x1d8
	ldr	r4, [pc, #72]	; 0x10b688
_01FF869C:
	cmp	r8, #472	; 0x1d8
	movhi	r6, r5
	movls	r6, r8
	mov	r0, sl
	mov	r1, r9
	mov	r2, fp
	orr	r3, r4, r6, lsr #2
	bl	MIi_DmaSetParams
	subs	r8, r8, r6
	add	r9, r9, r6
	bne	_01FF869C
_01FF86C8:
	ldr	r0, [r7]
	ands	r0, r0, #-2147483648	; 0x80000000
	bne	_01FF86C8
	add	sp, sp, #4
	ldmia sp!,	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_01FF86E0:	.word 0x040000B0
_01FF86E4:	.word 0x04000400
_01FF86E8:	.word 0x84400000
