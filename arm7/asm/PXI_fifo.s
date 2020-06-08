	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start PXIi_HandlerRecvFifoNotEmpty
PXIi_HandlerRecvFifoNotEmpty: ; 0x037FB5BC
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #8
	ldr	sl, _037FB6D0	; =0x04000184
	ldr	r5, _037FB6D4	; =_0380795C
	mov	r7, #68157440	; 0x4100000
	mov	r6, #0
	mvn	r8, #3
	mvn	r9, #2
	ldr	r4, _037FB6D8	; =0x04000188
_037FB5E0:
	ldrh	r0, [sl]
	ands	r0, r0, #16384	; 0x4000
	ldrneh	r0, [sl]
	orrne	r0, r0, #49152	; 0xc000
	strneh	r0, [sl]
	movne	r1, r9
	bne	_037FB628
	bl	OS_DisableInterrupts
	ldrh	r1, [sl]
	ands	r1, r1, #256	; 0x100
	beq	_037FB618
	bl	OS_RestoreInterrupts
	mov	r1, r8
	b	_037FB628
_037FB618:
	ldr	r1, [r7]
	str	r1, [sp]
	bl	OS_RestoreInterrupts
	mov	r1, r6
_037FB628:
	cmp	r1, r8
	beq	_037FB6C4
	mvn	r0, #2
	cmp	r1, r0
	beq	_037FB5E0
	ldr	r2, [sp]
	mov	r0, r2, lsl #27
	movs	r0, r0, lsr #27
	beq	_037FB5E0
	ldr	r3, [r5, r0, lsl #2]
	cmp	r3, #0
	beq	_037FB670
	mov	r1, r2, lsr #6
	mov	r2, r2, lsl #26
	mov	r2, r2, lsr #31
	mov	lr, pc
	bx	r3
	b	_037FB5E0
_037FB670:
	mov	r0, r2, lsl #26
	movs	r0, r0, lsr #31
	bne	_037FB5E0
	orr	r0, r2, #32
	str	r0, [sp]
	ldrh	r0, [sl]
	ands	r0, r0, #16384	; 0x4000
	ldrneh	r0, [sl]
	orrne	r0, r0, #49152	; 0xc000
	strneh	r0, [sl]
	bne	_037FB5E0
	bl	OS_DisableInterrupts
	ldrh	r1, [sl]
	ands	r1, r1, #2
	beq	_037FB6B4
	bl	OS_RestoreInterrupts
	b	_037FB5E0
_037FB6B4:
	ldr	r1, [sp]
	str	r1, [r4]
	bl	OS_RestoreInterrupts
	b	_037FB5E0
_037FB6C4:
	add	sp, sp, #8
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
_037FB6D0:	.word	0x04000184
_037FB6D4:	.word	_0380795C
_037FB6D8:	.word	0x04000188

	arm_func_start PXI_SendWordByFifo
PXI_SendWordByFifo: ; 0x037FB6DC
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r3, [sp]
	bic	r3, r3, #31
	and	r0, r0, #31
	orr	r0, r3, r0
	str	r0, [sp]
	bic	r3, r0, #32
	and	r0, r2, #1
	orr	r0, r3, r0, lsl #5
	str	r0, [sp]
	and	r2, r0, #63	; 0x3f
	bic	r0, r1, #-67108864	; 0xfc000000
	orr	r0, r2, r0, lsl #6
	str	r0, [sp]
	ldr	r1, _037FB778	; =0x04000184
	ldrh	r0, [r1]
	ands	r0, r0, #16384	; 0x4000
	ldrneh	r0, [r1]
	orrne	r0, r0, #49152	; 0xc000
	strneh	r0, [r1]
	mvnne	r0, #0
	bne	_037FB76C
	bl	OS_DisableInterrupts
	ldr	r1, _037FB778	; =0x04000184
	ldrh	r1, [r1]
	ands	r1, r1, #2
	beq	_037FB758
	bl	OS_RestoreInterrupts
	mvn	r0, #1
	b	_037FB76C
_037FB758:
	ldr	r2, [sp]
	ldr	r1, _037FB77C	; =0x04000188
	str	r2, [r1]
	bl	OS_RestoreInterrupts
	mov	r0, #0
_037FB76C:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB778:	.word	0x04000184
_037FB77C:	.word	0x04000188

	arm_func_start PXI_IsCallbackReady
PXI_IsCallbackReady: ; 0x037FB780
	mov	r3, #1
	mov	r2, r3, lsl r0
	ldr	r0, _037FB7A4	; =0x027FFC00
	add	r0, r0, r1, lsl #2
	ldr	r0, [r0, #904]	; 0x388
	ands	r0, r2, r0
	moveq	r3, #0
	mov	r0, r3
	bx	lr
_037FB7A4:	.word	0x027FFC00

	arm_func_start PXI_SetFifoRecvCallback
PXI_SetFifoRecvCallback: ; 0x037FB7A8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r5, r1
	bl	OS_DisableInterrupts
	ldr	r1, _037FB80C	; =_0380795C
	str	r5, [r1, r4, lsl #2]
	cmp	r5, #0
	beq	_037FB7E4
	ldr	r3, _037FB810	; =0x027FFC00
	ldr	r2, [r3, #908]	; 0x38c
	mov	r1, #1
	orr	r1, r2, r1, lsl r4
	str	r1, [r3, #908]	; 0x38c
	b	_037FB7FC
_037FB7E4:
	ldr	r3, _037FB810	; =0x027FFC00
	ldr	r2, [r3, #908]	; 0x38c
	mov	r1, #1
	mvn	r1, r1, lsl r4
	and	r1, r2, r1
	str	r1, [r3, #908]	; 0x38c
_037FB7FC:
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FB80C:	.word	_0380795C
_037FB810:	.word	0x027FFC00

	arm_func_start PXI_InitFifo
PXI_InitFifo: ; 0x037FB814
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	bl	OS_DisableInterrupts
	mov	r5, r0
	ldr	r0, _037FB8D4	; =_03807958
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FB8C4
	mov	r1, #1
	strh	r1, [r0]
	mov	r2, #0
	ldr	r0, _037FB8D8	; =0x027FFC00
	str	r2, [r0, #908]	; 0x38c
	mov	r1, r2
	ldr	r0, _037FB8DC	; =_0380795C
_037FB84C:
	str	r1, [r0, r2, lsl #2]
	add	r2, r2, #1
	cmp	r2, #32
	blt	_037FB84C
	ldr	r1, _037FB8E0	; =0x0000C408
	ldr	r0, _037FB8E4	; =0x04000184
	strh	r1, [r0]
	mov	r0, #262144	; 0x40000
	bl	OS_ResetRequestIrqMask
	mov	r0, #262144	; 0x40000
	ldr	r1, _037FB8E8	; =PXIi_HandlerRecvFifoNotEmpty
	bl	OS_SetIrqFunction
	mov	r0, #262144	; 0x40000
	bl	OS_EnableIrqMask
	mov	r4, #8
	mov	r6, r4
	ldr	r8, _037FB8EC	; =0x04000180
	mov	r7, #1000	; 0x3e8
	b	_037FB8BC
_037FB898:
	mov	r0, r4, lsl #8
	strh	r0, [r8]
	mov	r0, r7
	bl	OS_SpinWait
	ldrh	r0, [r8]
	and	r0, r0, #15
	cmp	r0, r4
	movne	r4, r6
	sub	r4, r4, #1
_037FB8BC:
	cmp	r4, #0
	bge	_037FB898
_037FB8C4:
	mov	r0, r5
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FB8D4:	.word	_03807958
_037FB8D8:	.word	0x027FFC00
_037FB8DC:	.word	_0380795C
_037FB8E0:	.word	0x0000C408
_037FB8E4:	.word	0x04000184
_037FB8E8:	.word	PXIi_HandlerRecvFifoNotEmpty
_037FB8EC:	.word	0x04000180
