	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OSi_IrqVBlank
OSi_IrqVBlank: ; 0x037F86B4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r0, _037F8700	; =OSi_IrqCallbackInfo
	ldr	r2, [r0, #96]	; 0x60
	ldr	r1, _037F8704	; =0x027FFC3C
	ldr	r0, [r1]
	add	r0, r0, #1
	str	r0, [r1]
	cmp	r2, #0
	beq	_037F86E4
	mov	lr, pc
	bx	r2
_037F86E4:
	ldr	r1, _037F8708	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, #1
	str	r0, [r1]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F8700:	.word	OSi_IrqCallbackInfo
_037F8704:	.word	0x027FFC3C
_037F8708:	.word	0x0380FFF8

	arm_func_start OSi_IrqTimer3
OSi_IrqTimer3: ; 0x037F870C
	mov	r0, #7
	ldr	ip, _037F8718	; =OSi_IrqCallback
	bx	ip
_037F8718:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqTimer2
OSi_IrqTimer2: ; 0x037F871C
	mov	r0, #6
	ldr	ip, _037F8728	; =OSi_IrqCallback
	bx	ip
_037F8728:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqTimer1
OSi_IrqTimer1: ; 0x037F872C
	mov	r0, #5
	ldr	ip, _037F8738	; =OSi_IrqCallback
	bx	ip
_037F8738:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqTimer0
OSi_IrqTimer0: ; 0x037F873C
	mov	r0, #4
	ldr	ip, _037F8748	; =OSi_IrqCallback
	bx	ip
_037F8748:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma3
OSi_IrqDma3: ; 0x037F874C
	mov	r0, #3
	ldr	ip, _037F8758	; =OSi_IrqCallback
	bx	ip
_037F8758:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma2
OSi_IrqDma2: ; 0x037F875C
	mov	r0, #2
	ldr	ip, _037F8768	; =OSi_IrqCallback
	bx	ip
_037F8768:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma1
OSi_IrqDma1: ; 0x037F876C
	mov	r0, #1
	ldr	ip, _037F8778	; =OSi_IrqCallback
	bx	ip
_037F8778:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqDma0
OSi_IrqDma0: ; 0x037F877C
	mov	r0, #0
	ldr	ip, _037F8788	; =OSi_IrqCallback
	bx	ip
_037F8788:	.word	OSi_IrqCallback

	arm_func_start OSi_IrqCallback
OSi_IrqCallback: ; 0x037F878C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r3, #1
	mov	r2, r0, lsl #1
	ldr	r1, _037F880C	; =_038075E4
	ldrh	r1, [r1, r2]
	mov	r5, r3, lsl r1
	mov	r1, #12
	mul	r4, r0, r1
	ldr	r2, _037F8810	; =OSi_IrqCallbackInfo
	ldr	r1, [r2, r4]
	mov	r0, #0
	str	r0, [r2, r4]
	cmp	r1, #0
	beq	_037F87D8
	ldr	r0, _037F8814	; =_0380771C
	ldr	r0, [r0, r4]
	mov	lr, pc
	bx	r1
_037F87D8:
	ldr	r1, _037F8818	; =0x0380FFF8
	ldr	r0, [r1]
	orr	r0, r0, r5
	str	r0, [r1]
	ldr	r0, _037F881C	; =_03807718
	ldr	r0, [r0, r4]
	cmp	r0, #0
	bne	_037F8800
	mov	r0, r5
	bl	OS_DisableIrqMask
_037F8800:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F880C:	.word	_038075E4
_037F8810:	.word	OSi_IrqCallbackInfo
_037F8814:	.word	_0380771C
_037F8818:	.word	0x0380FFF8
_037F881C:	.word	_03807718

	arm_func_start OS_IrqDummy
OS_IrqDummy: ; 0x037F8820
	bx	lr
