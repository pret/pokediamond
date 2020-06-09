	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03807744
_03807744: ;0x03807744
	.space 0x03807748 - 0x03807744

	.global _03807748
_03807748: ;0x03807748
	.space 0x0380774C - 0x03807748

	.global _0380774C
_0380774C: ;0x0380774C
	.space 0x03807774 - 0x0380774C

	.global _03807774
_03807774: ;0x03807774
	.space 0x03807780 - 0x03807774

    .section .text

	arm_func_start OS_ResetRequestIrqMask
OS_ResetRequestIrqMask: ; 0x037F8824
	ldr	ip, _037F8850	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F8854	; =0x04000214
	ldr	r1, [r2]
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F8850:	.word	0x04000208
_037F8854:	.word	0x04000214

	arm_func_start OS_DisableIrqMask
OS_DisableIrqMask: ; 0x037F8858
	ldr	ip, _037F888C	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F8890	; =0x04000210
	ldr	r1, [r2]
	mvn	r0, r0
	and	r0, r1, r0
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F888C:	.word	0x04000208
_037F8890:	.word	0x04000210

	arm_func_start OS_EnableIrqMask
OS_EnableIrqMask: ; 0x037F8894
	ldr	ip, _037F88C4	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F88C8	; =0x04000210
	ldr	r1, [r2]
	orr	r0, r1, r0
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F88C4:	.word	0x04000208
_037F88C8:	.word	0x04000210

	arm_func_start OS_SetIrqMask
OS_SetIrqMask: ; 0x037F88CC
	ldr	ip, _037F88F8	; =0x04000208
	ldrh	r3, [ip]
	mov	r1, #0
	strh	r1, [ip]
	ldr	r2, _037F88FC	; =0x04000210
	ldr	r1, [r2]
	str	r0, [r2]
	ldrh	r0, [ip]
	strh	r3, [ip]
	mov	r0, r1
	bx	lr
_037F88F8:	.word	0x04000208
_037F88FC:	.word	0x04000210

	arm_func_start OSi_EnterTimerCallback
OSi_EnterTimerCallback: ; 0x037F8900
	stmdb	sp!, {r4, lr}
	mov	r3, #12
	mul	r4, r0, r3
	ldr	r3, _037F8940	; =_03807744
	str	r1, [r3, r4]
	ldr	r1, _037F8944	; =_0380774C
	str	r2, [r1, r4]
	mov	r1, #1
	add	r0, r0, #3
	mov	r0, r1, lsl r0
	bl	OS_EnableIrqMask
	mov	r1, #1
	ldr	r0, _037F8948	; =_03807748
	str	r1, [r0, r4]
	ldmia	sp!, {r4, lr}
	bx	lr
_037F8940:	.word	_03807744
_037F8944:	.word	_0380774C
_037F8948:	.word	_03807748

	arm_func_start OS_SetIrqFunction
OS_SetIrqFunction: ; 0x037F894C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, #0
	mov	r7, r9
	ldr	lr, _037F89E8	; =OS_IRQTable
	ldr	r4, _037F89EC	; =_03807774
	ldr	r6, _037F89F0	; =OSi_IrqCallbackInfo
	mov	ip, r9
	mov	r3, #1
	mov	r2, #12
_037F8974:
	ands	r5, r0, #1
	beq	_037F89CC
	mov	r8, r7
	cmp	r9, #8
	blt	_037F8998
	cmp	r9, #11
	suble	r5, r9, #8
	mlale	r8, r5, r2, r6
	ble	_037F89BC
_037F8998:
	cmp	r9, #3
	blt	_037F89B0
	cmp	r9, #6
	addle	r5, r9, #1
	mlale	r8, r5, r2, r6
	ble	_037F89BC
_037F89B0:
	cmp	r9, #0
	moveq	r8, r4
	strne	r1, [lr, r9, lsl #2]
_037F89BC:
	cmp	r8, #0
	strne	r1, [r8]
	strne	ip, [r8, #8]
	strne	r3, [r8, #4]
_037F89CC:
	mov	r0, r0, lsr #1
	add	r9, r9, #1
	cmp	r9, #25
	blt	_037F8974
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr
_037F89E8:	.word	OS_IRQTable
_037F89EC:	.word	_03807774
_037F89F0:	.word	OSi_IrqCallbackInfo

	arm_func_start OS_InitIrqTable
OS_InitIrqTable: ; 0x037F89F4
	mov	r1, #0
	ldr	r0, _037F8A10	; =OSi_IrqThreadQueue
	str	r1, [r0, #4]
	str	r1, [r0]
	ldr	r0, _037F8A14	; =0x027FFC3C
	str	r1, [r0]
	bx	lr
_037F8A10:	.word	OSi_IrqThreadQueue
_037F8A14:	.word	0x027FFC3C
