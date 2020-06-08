	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SND_GetLfoValue
SND_GetLfoValue: ; 0x037FC7F4
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldrb	r0, [r4, #2]
	cmp	r0, #0
	moveq	r0, #0
	beq	_037FC83C
	ldrh	r1, [r4, #6]
	ldrh	r0, [r4, #4]
	cmp	r1, r0
	movcc	r0, #0
	bcc	_037FC83C
	ldrh	r0, [r4, #8]
	mov	r0, r0, lsr #8
	bl	SND_SinIdx
	ldrb	r2, [r4, #3]
	ldrb	r1, [r4, #2]
	mul	r0, r1, r0
	mul	r0, r2, r0
_037FC83C:
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start SND_UpdateLfo
SND_UpdateLfo: ; 0x037FC844
	ldrh	r2, [r0, #6]
	ldrh	r1, [r0, #4]
	cmp	r2, r1
	addcc	r1, r2, #1
	strcch	r1, [r0, #6]
	bxcc	lr
	ldrh	r2, [r0, #8]
	ldrb	r1, [r0, #1]
	mov	r3, r1, lsl #6
	add	r1, r2, r1, lsl #6
	mov	r2, r1, lsr #8
	b	_037FC878
_037FC874:
	sub	r2, r2, #128	; 0x80
_037FC878:
	cmp	r2, #128	; 0x80
	bcs	_037FC874
	ldrh	r1, [r0, #8]
	add	r1, r1, r3
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	and	r1, r1, #255	; 0xff
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	orr	r1, r1, r2, lsl #8
	strh	r1, [r0, #8]
	bx	lr

	arm_func_start SND_StartLfo
SND_StartLfo: ; 0x037FC8A8
	mov	r1, #0
	strh	r1, [r0, #8]
	strh	r1, [r0, #6]
	bx	lr

	arm_func_start SND_InitLfoParam
SND_InitLfoParam: ; 0x037FC8B8
	mov	r2, #0
	strb	r2, [r0]
	strb	r2, [r0, #2]
	mov	r1, #1
	strb	r1, [r0, #3]
	mov	r1, #16
	strb	r1, [r0, #1]
	strh	r2, [r0, #4]
	bx	lr
