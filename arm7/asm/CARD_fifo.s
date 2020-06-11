	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start CARDi_OnFifoRecv
CARDi_OnFifoRecv: ; 0x03800D2C
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	cmp	r0, #11
	bne	_03800DFC
	cmp	r2, #0
	beq	_03800DFC
	ldr	r0, _03800E08	; =cardi_common
	ldr	r2, [r0, #8]
	cmp	r2, #0
	streq	r1, [r0, #4]
	ldr	r2, [r0, #4]
	cmp	r2, #12
	addls	pc, pc, r2, lsl #2
	b	_03800DC8
	b	_03800D98
	b	_03800DC8
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
	b	_03800DBC
_03800D98:
	ldr	r2, [r0, #8]
	cmp	r2, #0
	beq	_03800DC8
	cmp	r2, #1
	streq	r1, [r0]
	ldreq	r1, [r0, #252]	; 0xfc
	orreq	r1, r1, #16
	streq	r1, [r0, #252]	; 0xfc
	b	_03800DC8
_03800DBC:
	ldr	r1, [r0, #252]	; 0xfc
	orr	r1, r1, #16
	str	r1, [r0, #252]	; 0xfc
_03800DC8:
	ldr	r1, [r0, #252]	; 0xfc
	ands	r1, r1, #16
	ldreq	r1, [r0, #8]
	addeq	r1, r1, #1
	streq	r1, [r0, #8]
	beq	_03800DFC
	mov	r1, #0
	str	r1, [r0, #8]
	ldr	r1, [r0, #252]	; 0xfc
	ands	r1, r1, #4
	ldrne	r0, [r0, #236]	; 0xec
	addeq	r0, r0, #72	; 0x48
	bl	OS_WakeupThreadDirect
_03800DFC:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03800E08:	.word	cardi_common

	arm_func_start FUN_03800E0C
FUN_03800E0C: ; 0x03800E0C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, r1
	mov	r5, #14
	mov	r4, #0
	b	_03800E30
_03800E28:
	mov	r0, r6
	bl	FUN_037F8CB4
_03800E30:
	mov	r0, r5
	mov	r1, r7
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03800E28
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
