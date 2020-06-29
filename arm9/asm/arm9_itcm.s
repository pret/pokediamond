	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	; MI
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
