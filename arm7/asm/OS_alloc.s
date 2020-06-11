	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global OSiHeapInfo
OSiHeapInfo: ;0x038078F8
	.space 0x0380791C - 0x038078F8

    .section .text

	arm_func_start OS_CheckHeap
OS_CheckHeap: ; 0x037F9D88
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, #0
	mov	r5, r6
	mvn	r4, #0
	bl	OS_DisableInterrupts
	ldr	r1, _037F9F34	; =OSiHeapInfo
	ldr	ip, [r1, r8, lsl #2]
	mov	r1, r4
	cmp	r7, r1
	ldreq	r7, [ip]
	ldr	r2, [ip, #16]
	cmp	r2, #0
	beq	_037F9F24
	cmp	r7, #0
	blt	_037F9F24
	ldr	r1, [ip, #4]
	cmp	r7, r1
	bge	_037F9F24
	mov	r1, #12
	mul	r1, r7, r1
	add	r3, r2, r1
	ldr	r2, [r2, r1]
	cmp	r2, #0
	blt	_037F9F24
	ldr	r1, [r3, #8]
	cmp	r1, #0
	beq	_037F9E70
	ldr	r7, [r1]
	cmp	r7, #0
	bne	_037F9F24
	b	_037F9E70
_037F9E0C:
	ldr	r7, [ip, #8]
	cmp	r7, r1
	bhi	_037F9F24
	ldr	r7, [ip, #12]
	cmp	r1, r7
	bcs	_037F9F24
	ands	r7, r1, #31
	bne	_037F9F24
	ldr	lr, [r1, #4]
	cmp	lr, #0
	beq	_037F9E44
	ldr	r7, [lr]
	cmp	r7, r1
	bne	_037F9F24
_037F9E44:
	ldr	r7, [r1, #8]
	cmp	r7, #64	; 0x40
	bcc	_037F9F24
	ands	r1, r7, #31
	bne	_037F9F24
	add	r6, r6, r7
	cmp	r6, #0
	ble	_037F9F24
	cmp	r6, r2
	bgt	_037F9F24
	mov	r1, lr
_037F9E70:
	cmp	r1, #0
	bne	_037F9E0C
	ldr	r1, [r3, #4]
	cmp	r1, #0
	beq	_037F9F14
	ldr	r3, [r1]
	cmp	r3, #0
	bne	_037F9F24
	b	_037F9F14
_037F9E94:
	ldr	r3, [ip, #8]
	cmp	r3, r1
	bhi	_037F9F24
	ldr	r3, [ip, #12]
	cmp	r1, r3
	bcs	_037F9F24
	ands	r3, r1, #31
	bne	_037F9F24
	ldr	lr, [r1, #4]
	cmp	lr, #0
	beq	_037F9ECC
	ldr	r3, [lr]
	cmp	r3, r1
	bne	_037F9F24
_037F9ECC:
	ldr	r7, [r1, #8]
	cmp	r7, #64	; 0x40
	bcc	_037F9F24
	ands	r3, r7, #31
	bne	_037F9F24
	cmp	lr, #0
	beq	_037F9EF4
	add	r1, r1, r7
	cmp	r1, lr
	bcs	_037F9F24
_037F9EF4:
	add	r6, r6, r7
	sub	r1, r7, #32
	add	r5, r5, r1
	cmp	r6, #0
	ble	_037F9F24
	cmp	r6, r2
	bgt	_037F9F24
	mov	r1, lr
_037F9F14:
	cmp	r1, #0
	bne	_037F9E94
	cmp	r6, r2
	moveq	r4, r5
_037F9F24:
	bl	OS_RestoreInterrupts
	mov	r0, r4
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037F9F34:	.word	OSiHeapInfo

	arm_func_start OS_CreateHeap
OS_CreateHeap: ; 0x037F9F38
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r6, r1
	mov	r5, r2
	bl	OS_DisableInterrupts
	ldr	r1, _037F9FDC	; =OSiHeapInfo
	ldr	r7, [r1, r4, lsl #2]
	add	r1, r6, #31
	bic	r6, r1, #31
	bic	r5, r5, #31
	mov	r4, #0
	ldr	lr, [r7, #4]
	mov	r1, #12
	b	_037F9FC0
_037F9F74:
	ldr	r3, [r7, #16]
	mul	r2, r4, r1
	add	ip, r3, r2
	ldr	r2, [r3, r2]
	cmp	r2, #0
	bge	_037F9FBC
	sub	r1, r5, r6
	str	r1, [ip]
	mov	r2, #0
	str	r2, [r6]
	str	r2, [r6, #4]
	ldr	r1, [ip]
	str	r1, [r6, #8]
	str	r6, [ip, #4]
	str	r2, [ip, #8]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	b	_037F9FD0
_037F9FBC:
	add	r4, r4, #1
_037F9FC0:
	cmp	r4, lr
	blt	_037F9F74
	bl	OS_RestoreInterrupts
	mvn	r0, #0
_037F9FD0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037F9FDC:	.word	OSiHeapInfo

	arm_func_start OS_InitAlloc
OS_InitAlloc: ; 0x037F9FE0
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r5, r1
	mov	r4, r2
	mov	r6, r3
	bl	OS_DisableInterrupts
	ldr	r1, _037FA084	; =OSiHeapInfo
	str	r5, [r1, r7, lsl #2]
	mov	r2, #12
	mul	r1, r6, r2
	add	r3, r5, #20
	str	r3, [r5, #16]
	str	r6, [r5, #4]
	mov	r8, #0
	mvn	lr, #0
	mov	ip, r8
	b	_037FA044
_037FA024:
	ldr	r6, [r5, #16]
	mul	r3, r8, r2
	add	r7, r6, r3
	str	lr, [r6, r3]
	str	ip, [r7, #8]
	ldr	r3, [r7, #8]
	str	r3, [r7, #4]
	add	r8, r8, #1
_037FA044:
	ldr	r3, [r5, #4]
	cmp	r8, r3
	blt	_037FA024
	mvn	r2, #0
	str	r2, [r5]
	ldr	r2, [r5, #16]
	add	r1, r2, r1
	add	r1, r1, #31
	bic	r1, r1, #31
	str	r1, [r5, #8]
	bic	r1, r4, #31
	str	r1, [r5, #12]
	bl	OS_RestoreInterrupts
	ldr	r0, [r5, #8]
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FA084:	.word	OSiHeapInfo

	arm_func_start OS_SetCurrentHeap
OS_SetCurrentHeap: ; 0x037FA088
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r5, r1
	bl	OS_DisableInterrupts
	ldr	r1, _037FA0C0	; =OSiHeapInfo
	ldr	r1, [r1, r4, lsl #2]
	ldr	r4, [r1]
	str	r5, [r1]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FA0C0:	.word	OSiHeapInfo

	arm_func_start OS_FreeToHeap
OS_FreeToHeap: ; 0x037FA0C4
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r4, r1
	mov	r6, r2
	bl	OS_DisableInterrupts
	mov	r5, r0
	ldr	r0, _037FA134	; =OSiHeapInfo
	ldr	r0, [r0, r7, lsl #2]
	cmp	r4, #0
	ldrlt	r4, [r0]
	sub	r6, r6, #32
	ldr	r1, [r0, #16]
	mov	r0, #12
	mla	r7, r4, r0, r1
	ldr	r0, [r7, #8]
	mov	r1, r6
	bl	DLExtract
	str	r0, [r7, #8]
	ldr	r0, [r7, #4]
	mov	r1, r6
	bl	DLInsert
	str	r0, [r7, #4]
	mov	r0, r5
	bl	OS_RestoreInterrupts
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FA134:	.word	OSiHeapInfo

	arm_func_start OS_AllocFromHeap
OS_AllocFromHeap: ; 0x037FA138
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	mov	r5, r1
	mov	r7, r2
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r1, _037FA24C	; =OSiHeapInfo
	ldr	r1, [r1, r6, lsl #2]
	cmp	r1, #0
	bne	_037FA170
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037FA240
_037FA170:
	cmp	r5, #0
	ldrlt	r5, [r1]
	ldr	r1, [r1, #16]
	mov	r0, #12
	mla	r6, r5, r0, r1
	add	r0, r7, #32
	add	r0, r0, #31
	bic	r7, r0, #31
	ldr	r0, [r6, #4]
	mov	r5, r0
	b	_037FA1AC
_037FA19C:
	ldr	r1, [r5, #8]
	cmp	r7, r1
	ble	_037FA1B4
	ldr	r5, [r5, #4]
_037FA1AC:
	cmp	r5, #0
	bne	_037FA19C
_037FA1B4:
	cmp	r5, #0
	bne	_037FA1CC
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, #0
	b	_037FA240
_037FA1CC:
	ldr	r1, [r5, #8]
	sub	r1, r1, r7
	cmp	r1, #64	; 0x40
	bcs	_037FA1EC
	mov	r1, r5
	bl	DLExtract
	str	r0, [r6, #4]
	b	_037FA224
_037FA1EC:
	str	r7, [r5, #8]
	add	r2, r5, r7
	str	r1, [r2, #8]
	ldr	r0, [r5]
	str	r0, [r5, r7]
	ldr	r0, [r5, #4]
	str	r0, [r2, #4]
	ldr	r0, [r2, #4]
	cmp	r0, #0
	strne	r2, [r0]
	ldr	r0, [r2]
	cmp	r0, #0
	strne	r2, [r0, #4]
	streq	r2, [r6, #4]
_037FA224:
	ldr	r0, [r6, #8]
	mov	r1, r5
	bl	DLAddFront
	str	r0, [r6, #8]
	mov	r0, r4
	bl	OS_RestoreInterrupts
	add	r0, r5, #32
_037FA240:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FA24C:	.word	OSiHeapInfo

	arm_func_start DLInsert
DLInsert: ; 0x037FA250
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	ip, r0
	mov	lr, #0
	b	_037FA274
_037FA264:
	cmp	r1, ip
	bls	_037FA27C
	mov	lr, ip
	ldr	ip, [ip, #4]
_037FA274:
	cmp	ip, #0
	bne	_037FA264
_037FA27C:
	str	ip, [r1, #4]
	str	lr, [r1]
	cmp	ip, #0
	beq	_037FA2BC
	str	r1, [ip]
	ldr	r3, [r1, #8]
	add	r2, r1, r3
	cmp	r2, ip
	bne	_037FA2BC
	ldr	r2, [ip, #8]
	add	r2, r3, r2
	str	r2, [r1, #8]
	ldr	ip, [ip, #4]
	str	ip, [r1, #4]
	cmp	ip, #0
	strne	r1, [ip]
_037FA2BC:
	cmp	lr, #0
	beq	_037FA2F4
	str	r1, [lr, #4]
	ldr	r2, [lr, #8]
	add	r3, lr, r2
	cmp	r3, r1
	bne	_037FA2F8
	ldr	r1, [r1, #8]
	add	r1, r2, r1
	str	r1, [lr, #8]
	str	ip, [lr, #4]
	cmp	ip, #0
	strne	lr, [ip]
	b	_037FA2F8
_037FA2F4:
	mov	r0, r1
_037FA2F8:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start DLExtract
DLExtract: ; 0x037FA304
	ldr	r3, [r1, #4]
	cmp	r3, #0
	ldrne	r2, [r1]
	strne	r2, [r3]
	ldr	r2, [r1]
	cmp	r2, #0
	ldreq	r0, [r1, #4]
	ldrne	r1, [r1, #4]
	strne	r1, [r2, #4]
	bx	lr

	arm_func_start DLAddFront
DLAddFront: ; 0x037FA32C
	str	r0, [r1, #4]
	mov	r2, #0
	str	r2, [r1]
	cmp	r0, #0
	strne	r1, [r0]
	mov	r0, r1
	bx	lr
