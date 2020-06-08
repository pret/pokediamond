	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start MI_StopDma
MI_StopDma: ; 0x037FB20C
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	OS_DisableInterrupts
	mov	r1, #6
	mul	r1, r4, r1
	add	r1, r1, #5
	mov	r1, r1, lsl #1
	add	r1, r1, #67108864	; 0x4000000
	ldrh	r2, [r1, #176]	; 0xb0
	bic	r2, r2, #12800	; 0x3200
	strh	r2, [r1, #176]	; 0xb0
	ldrh	r2, [r1, #176]	; 0xb0
	bic	r2, r2, #32768	; 0x8000
	strh	r2, [r1, #176]	; 0xb0
	ldrh	r2, [r1, #176]	; 0xb0
	ldrh	r1, [r1, #176]	; 0xb0
	cmp	r4, #0
	bne	_037FB27C
	mov	r1, #12
	mul	r3, r4, r1
	ldr	r1, _037FB288	; =0x040000B0
	add	r4, r3, r1
	mov	r2, #0
	add	r1, r3, #67108864	; 0x4000000
	str	r2, [r1, #176]	; 0xb0
	str	r2, [r4, #4]
	ldr	r1, _037FB28C	; =0x81400001
	str	r1, [r4, #8]
_037FB27C:
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr
_037FB288:	.word	0x040000B0
_037FB28C:	.word	0x81400001

	arm_func_start MI_WaitDma
MI_WaitDma: ; 0x037FB290
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	bl	OS_DisableInterrupts
	mov	r1, #3
	mul	r1, r4, r1
	add	r2, r1, #2
	ldr	r1, _037FB2F8	; =0x040000B0
	add	r2, r1, r2, lsl #2
_037FB2B0:
	ldr	r1, [r2]
	ands	r1, r1, #-2147483648	; 0x80000000
	bne	_037FB2B0
	cmp	r4, #0
	bne	_037FB2EC
	mov	r1, #12
	mul	r3, r4, r1
	ldr	r1, _037FB2F8	; =0x040000B0
	add	r4, r3, r1
	mov	r2, #0
	add	r1, r3, #67108864	; 0x4000000
	str	r2, [r1, #176]	; 0xb0
	str	r2, [r4, #4]
	ldr	r1, _037FB2FC	; =0x81400001
	str	r1, [r4, #8]
_037FB2EC:
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr
_037FB2F8:	.word	0x040000B0
_037FB2FC:	.word	0x81400001
