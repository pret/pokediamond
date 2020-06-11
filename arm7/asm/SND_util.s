	.include "asm/macros.inc"
	.include "global.inc"

    .section .data

	.global _03807660
_03807660:
	.word	0x12345678

    .section .text

	arm_func_start SND_CalcRandom
SND_CalcRandom: ; 0x037FC058
	ldr	r2, _037FC080	; =_03807660
	ldr	r3, [r2]
	ldr	r0, _037FC084	; =0x0019660D
	ldr	r1, _037FC088	; =0x3C6EF35F
	mla	r0, r3, r0, r1
	str	r0, [r2]
	mov	r0, r0, lsr #16
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	bx	lr
_037FC080:	.word	_03807660
_037FC084:	.word	0x0019660D
_037FC088:	.word	0x3C6EF35F

	arm_func_start SND_SinIdx
SND_SinIdx: ; 0x037FC08C
	cmp	r0, #32
	ldrlt	r1, _037FC0F4	; =_03807170
	ldrltsb	r0, [r1, r0]
	bxlt	lr
	cmp	r0, #64	; 0x40
	rsblt	r1, r0, #64	; 0x40
	ldrlt	r0, _037FC0F4	; =_03807170
	ldrltsb	r0, [r0, r1]
	bxlt	lr
	cmp	r0, #96	; 0x60
	bge	_037FC0D4
	sub	r1, r0, #64	; 0x40
	ldr	r0, _037FC0F4	; =_03807170
	ldrsb	r0, [r0, r1]
	rsb	r0, r0, #0
	mov	r0, r0, lsl #24
	mov	r0, r0, asr #24
	bx	lr
_037FC0D4:
	sub	r0, r0, #96	; 0x60
	rsb	r1, r0, #32
	ldr	r0, _037FC0F4	; =_03807170
	ldrsb	r0, [r0, r1]
	rsb	r0, r0, #0
	mov	r0, r0, lsl #24
	mov	r0, r0, asr #24
	bx	lr
_037FC0F4:	.word	_03807170

	arm_func_start SND_CalcChannelVolume
SND_CalcChannelVolume: ; 0x037FC0F8
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FC168	; =0xFFFFFD2D
	cmp	r4, r0
	movlt	r4, r0
	blt	_037FC118
	cmp	r4, #0
	movgt	r4, #0
_037FC118:
	ldr	r0, _037FC16C	; =0x000002D3
	add	r0, r4, r0
	bl	FUN_037FC170
	mvn	r1, #239	; 0xef
	cmp	r4, r1
	movlt	r1, #3
	blt	_037FC154
	mvn	r1, #119	; 0x77
	cmp	r4, r1
	movlt	r1, #2
	blt	_037FC154
	mvn	r1, #59	; 0x3b
	cmp	r4, r1
	movlt	r1, #1
	movge	r1, #0
_037FC154:
	orr	r0, r0, r1, lsl #8
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	ldmia	sp!, {r4, lr}
	bx	lr
_037FC168:	.word	0xFFFFFD2D
_037FC16C:	.word	0x000002D3

	arm_func_start FUN_037FC170
FUN_037FC170: ; 0x037FC170
	ldr	ip, _037FC178	; =SVC_GetVolumeTable
	bx	ip
_037FC178:	.word	SVC_GetVolumeTable

	arm_func_start SND_CalcTimer
SND_CalcTimer: ; 0x037FC17C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, #0
	rsb	r0, r1, #0
	b	_037FC19C
_037FC194:
	sub	r4, r4, #1
	add	r0, r0, #768	; 0x300
_037FC19C:
	cmp	r0, #0
	blt	_037FC194
	b	_037FC1B0
_037FC1A8:
	add	r4, r4, #1
	sub	r0, r0, #768	; 0x300
_037FC1B0:
	cmp	r0, #768	; 0x300
	bge	_037FC1A8
	bl	FUN_037FC2A4
	mov	r2, #0
	mov	r1, #65536	; 0x10000
	adds	lr, r0, r1
	adc	ip, r2, #0
	mov	r3, r5, asr #31
	umull	r1, r0, lr, r5
	mla	r0, lr, r3, r0
	mla	r0, ip, r5, r0
	sub	lr, r4, #16
	cmp	lr, #0
	bgt	_037FC208
	rsb	r2, lr, #0
	mov	r3, r0, lsr r2
	mov	r5, r1, lsr r2
	rsb	r1, r2, #32
	orr	r5, r5, r0, lsl r1
	sub	r1, r2, #32
	orr	r5, r5, r0, lsr r1
	b	_037FC264
_037FC208:
	cmp	lr, #32
	bge	_037FC25C
	mvn	r5, #0
	rsb	r4, lr, #32
	mov	ip, r5, lsl r4
	rsb	r3, r4, #32
	orr	ip, ip, r5, lsr r3
	sub	r3, r4, #32
	orr	ip, ip, r5, lsl r3
	and	r3, r0, ip
	and	r5, r1, r5, lsl r4
	cmp	r3, r2
	cmpeq	r5, r2
	ldrne	r0, _037FC2A0	; =0x0000FFFF
	bne	_037FC294
	mov	r5, r1, lsl lr
	mov	r3, r0, lsl lr
	orr	r3, r3, r1, lsr r4
	sub	r0, lr, #32
	orr	r3, r3, r1, lsl r0
	b	_037FC264
_037FC25C:
	ldr	r0, _037FC2A0	; =0x0000FFFF
	b	_037FC294
_037FC264:
	mov	r1, #0
	mov	r0, #16
	cmp	r3, r1
	cmpeq	r5, r0
	movcc	r5, r0
	bcc	_037FC28C
	ldr	r0, _037FC2A0	; =0x0000FFFF
	cmp	r3, r1
	cmpeq	r5, r0
	movhi	r5, r0
_037FC28C:
	mov	r0, r5, lsl #16
	mov	r0, r0, lsr #16
_037FC294:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FC2A0:	.word	0x0000FFFF

	arm_func_start FUN_037FC2A4
FUN_037FC2A4: ; 0x037FC2A4
	ldr	ip, _037FC2AC	; =SVC_GetPitchTable
	bx	ip
_037FC2AC:	.word	SVC_GetPitchTable
