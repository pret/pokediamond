	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OS_ResetSystem
OS_ResetSystem: ; 0x037FB0E0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	MI_StopDma
	mov	r0, #1
	bl	MI_StopDma
	mov	r0, #2
	bl	MI_StopDma
	mov	r0, #3
	bl	MI_StopDma
	mov	r0, #262144	; 0x40000
	bl	OS_SetIrqMask
	mvn	r0, #0
	bl	OS_ResetRequestIrqMask
	bl	SND_Shutdown
	mov	r0, #16
	bl	OSi_SendToPxi
	bl	FUN_038073EC
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start OSi_SendToPxi
OSi_SendToPxi: ; 0x037FB134
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0, lsl #8
	mov	r5, #12
	mov	r4, #0
_037FB144:
	mov	r0, r5
	mov	r1, r6
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_037FB144
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start OSi_CommonCallback
OSi_CommonCallback: ; 0x037FB164
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #32512	; 0x7f00
	mov	r0, r0, lsl #8
	mov	r0, r0, lsr #16
	cmp	r0, #16
	moveq	r1, #1
	ldreq	r0, _037FB19C	; =_03807954
	streqh	r1, [r0]
	beq	_037FB190
	bl	OS_Terminate
_037FB190:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB19C:	.word	_03807954

	arm_func_start OS_IsResetOccurred
OS_IsResetOccurred: ; 0x037FB1A0
	ldr	r0, _037FB1AC	; =_03807954
	ldrh	r0, [r0]
	bx	lr
_037FB1AC:	.word	_03807954

	arm_func_start OS_InitReset
OS_InitReset: ; 0x037FB1B0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037FB1E8	; =_03807950
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_037FB1DC
	mov	r1, #1
	strh	r1, [r0]
	mov	r0, #12
	ldr	r1, _037FB1EC	; =OSi_CommonCallback
	bl	PXI_SetFifoRecvCallback
_037FB1DC:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037FB1E8:	.word	_03807950
_037FB1EC:	.word	OSi_CommonCallback
