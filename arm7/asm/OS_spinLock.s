	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03807780
_03807780: ;0x03807780
	.space 0x03807784 - 0x03807780

    .section .text

	arm_func_start OS_UnLockCartridge
OS_UnLockCartridge: ; 0x037F8A18
	ldr	r1, _037F8A20	; =OS_UnlockCartridge
	bx	r1
_037F8A20:	.word	OS_UnlockCartridge

	arm_func_start OS_GetLockID
OS_GetLockID: ; 0x037F8A24
	ldr	r3, _037F8AB4	; =0x027FFFB8
	ldr	r1, [r3]
	mov	r2, #0
	mov	r0, #-2147483648	; 0x80000000
_037F8A34:
	tst	r1, r0
	bne	_037F8A50
	add	r2, r2, #1
	cmp	r2, #32
	beq	_037F8A50
	mov	r0, r0, lsr #1
	b	_037F8A34
_037F8A50:
	cmp	r2, #32
	movne	r0, #128	; 0x80
	bne	_037F8A98
	add	r3, r3, #4
	ldr	r1, [r3]
	mov	r2, #0
	mov	r0, #-2147483648	; 0x80000000
_037F8A6C:
	tst	r1, r0
	bne	_037F8A88
	add	r2, r2, #1
	cmp	r2, #32
	beq	_037F8A88
	mov	r0, r0, lsr #1
	b	_037F8A6C
_037F8A88:
	cmp	r2, #32
	ldr	r0, _037F8AB8	; =0xFFFFFFFD
	bxeq	lr
	mov	r0, #160	; 0xa0
_037F8A98:
	add	r0, r0, r2
	mov	r1, #-2147483648	; 0x80000000
	mov	r1, r1, lsr r2
	ldr	r2, [r3]
	bic	r2, r2, r1
	str	r2, [r3]
	bx	lr
_037F8AB4:	.word	0x027FFFB8
_037F8AB8:	.word	0xFFFFFFFD

	arm_func_start OS_ReleaseLockID
OS_ReleaseLockID: ; 0x037F8ABC
	ldr	r3, _037F8AE8	; =0x027FFFB8
	cmp	r0, #160	; 0xa0
	addpl	r3, r3, #4
	subpl	r0, r0, #160	; 0xa0
	submi	r0, r0, #128	; 0x80
	mov	r1, #-2147483648	; 0x80000000
	mov	r1, r1, lsr r0
	ldr	r2, [r3]
	orr	r2, r2, r1
	str	r2, [r3]
	bx	lr
_037F8AE8:	.word	0x027FFFB8

	arm_func_start OS_ReadOwnerOfLockWord
OS_ReadOwnerOfLockWord: ; 0x037F8AEC
	ldrh	r0, [r0, #4]
	bx	lr

	arm_func_start OSi_FreeCartridgeBus
OSi_FreeCartridgeBus: ;0x037F8AF4
	bx	lr

	arm_func_start OSi_AllocateCartridgeBus
OSi_AllocateCartridgeBus: ;0x037F8AF8
	bx	lr

	arm_func_start OS_TryLockCartridge
OS_TryLockCartridge: ; 0x037F8AFC
	ldr	r1, _037F8B10	; =0x027FFFE8
	ldr	r2, _037F8B14	; =OSi_AllocateCartridgeBus
	mov	r3, #1
	ldr	ip, _037F8B18	; =OSi_DoTryLockByWord
	bx	ip
_037F8B10:	.word	0x027FFFE8
_037F8B14:	.word	OSi_AllocateCartridgeBus
_037F8B18:	.word	OSi_DoTryLockByWord

	arm_func_start OS_UnlockCartridge
OS_UnlockCartridge: ; 0x037F8B1C
	ldr	r1, _037F8B30	; =0x027FFFE8
	ldr	r2, _037F8B34	; =OSi_FreeCartridgeBus
	mov	r3, #1
	ldr	ip, _037F8B38	; =OSi_DoUnlockByWord
	bx	ip
_037F8B30:	.word	0x027FFFE8
_037F8B34:	.word	OSi_FreeCartridgeBus
_037F8B38:	.word	OSi_DoUnlockByWord

	arm_func_start OS_LockCartridge
OS_LockCartridge: ; 0x037F8B3C
	ldr	r1, _037F8B50	; =0x027FFFE8
	ldr	r2, _037F8B54	; =OSi_AllocateCartridgeBus
	mov	r3, #1
	ldr	ip, _037F8B58	; =OSi_DoLockByWord
	bx	ip
_037F8B50:	.word	0x027FFFE8
_037F8B54:	.word	OSi_AllocateCartridgeBus
_037F8B58:	.word	OSi_DoLockByWord

	arm_func_start OSi_DoTryLockByWord
OSi_DoTryLockByWord: ; 0x037F8B5C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #4
	mov	r9, r0
	mov	r8, r1
	mov	r7, r2
	movs	r6, r3
	beq	_037F8B84
	bl	OS_DisableInterrupts_IrqAndFiq
	mov	r5, r0
	b	_037F8B8C
_037F8B84:
	bl	OS_DisableInterrupts
	mov	r5, r0
_037F8B8C:
	mov	r0, r9
	mov	r1, r8
	bl	MI_SwapWord
	movs	r4, r0
	bne	_037F8BB4
	cmp	r7, #0
	beq	_037F8BB0
	mov	lr, pc
	bx	r7
_037F8BB0:
	strh	r9, [r8, #4]
_037F8BB4:
	cmp	r6, #0
	beq	_037F8BC8
	mov	r0, r5
	bl	OS_RestoreInterrupts_IrqAndFiq
	b	_037F8BD0
_037F8BC8:
	mov	r0, r5
	bl	OS_RestoreInterrupts
_037F8BD0:
	mov	r0, r4
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, lr}
	bx	lr

	arm_func_start OSi_DoUnlockByWord
OSi_DoUnlockByWord: ; 0x037F8BE0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	ldrh	r1, [r7, #4]
	cmp	r0, r1
	mvnne	r0, #1
	bne	_037F8C60
	cmp	r5, #0
	beq	_037F8C18
	bl	OS_DisableInterrupts_IrqAndFiq
	mov	r4, r0
	b	_037F8C20
_037F8C18:
	bl	OS_DisableInterrupts
	mov	r4, r0
_037F8C20:
	mov	r0, #0
	strh	r0, [r7, #4]
	cmp	r6, #0
	beq	_037F8C38
	mov	lr, pc
	bx	r6
_037F8C38:
	mov	r0, #0
	str	r0, [r7]
	cmp	r5, #0
	beq	_037F8C54
	mov	r0, r4
	bl	OS_RestoreInterrupts_IrqAndFiq
	b	_037F8C5C
_037F8C54:
	mov	r0, r4
	bl	OS_RestoreInterrupts
_037F8C5C:
	mov	r0, #0
_037F8C60:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start OSi_DoLockByWord
OSi_DoLockByWord: ; 0x037F8C6C
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	mov	r4, #1024	; 0x400
	b	_037F8C90
_037F8C88:
	mov	r0, r4
	bl	FUN_037F8CB4
_037F8C90:
	mov	r0, r8
	mov	r1, r7
	mov	r2, r6
	mov	r3, r5
	bl	OSi_DoTryLockByWord
	cmp	r0, #0
	bgt	_037F8C88
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start FUN_037F8CB4
FUN_037F8CB4: ; 0x037F8CB4 ;part of the above func?
	ldr	ip, _037F8CBC	; =SVC_WaitByLoop
	bx	ip
_037F8CBC:	.word	SVC_WaitByLoop

	arm_func_start OS_InitLock
OS_InitLock: ; 0x037F8CC0
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	ldr	r0, _037F8D38	; =_03807780
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_037F8D2C
	mov	r1, #1
	str	r1, [r0]
	mov	r0, #0
	ldr	r4, _037F8D3C	; =0x027FFFF0
	strh	r0, [r4, #6]
	mov	r5, #1024	; 0x400
	b	_037F8CFC
_037F8CF4:
	mov	r0, r5
	bl	FUN_037F8CB4
_037F8CFC:
	ldrh	r0, [r4, #4]
	cmp	r0, #127	; 0x7f
	bne	_037F8CF4
	mvn	r1, #0
	ldr	r0, _037F8D40	; =0x027FFFB8
	str	r1, [r0]
	mov	r0, #65536	; 0x10000
	rsb	r1, r0, #0
	ldr	r0, _037F8D44	; =0x027FFFBC
	str	r1, [r0]
	mov	r0, #191	; 0xbf
	strh	r0, [r4, #6]
_037F8D2C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037F8D38:	.word	_03807780
_037F8D3C:	.word	0x027FFFF0
_037F8D40:	.word	0x027FFFB8
_037F8D44:	.word	0x027FFFBC
