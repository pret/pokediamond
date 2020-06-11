	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SND_InvalidateWave
SND_InvalidateWave: ; 0x037FC8DC
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, #0
	mov	r9, r5
	ldr	r4, _037FC960	; =SNDi_Work
	mov	r8, #84	; 0x54
_037FC8FC:
	mla	r2, r5, r8, r4
	ldrb	r1, [r2, #3]
	mov	r0, r1, lsl #31
	movs	r0, r0, lsr #31
	beq	_037FC944
	ldrb	r0, [r2, #1]
	cmp	r0, #0
	bne	_037FC944
	ldr	r0, [r2, #68]	; 0x44
	cmp	r7, r0
	bhi	_037FC944
	cmp	r0, r6
	bhi	_037FC944
	bic	r0, r1, #2
	strb	r0, [r2, #3]
	mov	r0, r5
	mov	r1, r9
	bl	SND_StopChannel
_037FC944:
	add	r0, r5, #1
	and	r5, r0, #255	; 0xff
	cmp	r5, #16
	bcc	_037FC8FC
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037FC960:	.word	SNDi_Work
