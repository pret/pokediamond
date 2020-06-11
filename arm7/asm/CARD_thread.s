	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start CARDi_TaskThread
CARDi_TaskThread: ; 0x03800B20
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	ldr	r9, _03800D28	; =cardi_common
	add	r5, r9, #72	; 0x48
	mov	r8, #0
	add	r7, r9, #252	; 0xfc
	mov	r6, #1
	mov	r4, #3
	mov	fp, #11
_03800B44:
	mov	sl, r8
	bl	OS_DisableInterrupts
	str	r0, [sp]
_03800B50:
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #4
	bne	_03800B88
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_03800B94
	ldr	r0, [r7]
	orr	r0, r0, #4
	str	r0, [r7]
	ldr	r0, [r7]
	bic	r0, r0, #16
	str	r0, [r7]
	mov	sl, r6
	b	_03800BA4
_03800B88:
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #8
	bne	_03800BA4
_03800B94:
	str	r5, [r9, #236]	; 0xec
	mov	r0, r8
	bl	OS_SleepThread
	b	_03800B50
_03800BA4:
	ldr	r0, [sp]
	bl	OS_RestoreInterrupts
	cmp	sl, #0
	beq	_03800D14
	ldr	r0, [r9]
	str	r8, [r0]
	ldr	r2, [r9]
	ldr	r1, [r2, #76]	; 0x4c
	ldr	r0, [r9, #4]
	mov	r0, r6, lsl r0
	ands	r0, r1, r0
	streq	r4, [r2]
	ldr	r0, [r9, #4]
	cmp	r0, #12
	addls	pc, pc, r0, lsl #2
	b	_03800CB8
	b	_03800CC0
	b	_03800CC0
	b	_03800C18
	b	_03800C20
	b	_03800C30
	b	_03800CB8
	b	_03800C3C
	b	_03800C54
	b	_03800C6C
	b	_03800C84
	b	_03800CB8
	b	_03800C9C
	b	_03800CB0
_03800C18:
	bl	CARDi_InitStatusRegister
	b	_03800CC0
_03800C20:
	bl	CARDi_ReadRomIDCore
	ldr	r1, [r9]
	str	r0, [r1, #8]
	b	_03800CC0
_03800C30:
	ldr	r0, [r9]
	str	r4, [r0]
	b	_03800CC0
_03800C3C:
	ldr	r2, [r9]
	ldr	r0, [r2, #12]
	ldr	r1, [r2, #16]
	ldr	r2, [r2, #20]
	bl	CARDi_ReadBackupCore
	b	_03800CC0
_03800C54:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_WriteBackupCore
	b	_03800CC0
_03800C6C:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_ProgramBackupCore
	b	_03800CC0
_03800C84:
	ldr	r2, [r9]
	ldr	r0, [r2, #16]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #20]
	bl	CARDi_VerifyBackupCore
	b	_03800CC0
_03800C9C:
	ldr	r1, [r9]
	ldr	r0, [r1, #16]
	ldr	r1, [r1, #20]
	bl	CARDi_EraseBackupSectorCore
	b	_03800CC0
_03800CB0:
	bl	CARDi_EraseChipCore
	b	_03800CC0
_03800CB8:
	ldr	r0, [r9]
	str	r4, [r0]
_03800CC0:
	mov	r0, fp
	mov	r1, r6
	mov	r2, r6
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	blt	_03800CC0
	bl	OS_DisableInterrupts
	mov	sl, r0
	ldr	r0, [r9, #252]	; 0xfc
	bic	r0, r0, #76	; 0x4c
	str	r0, [r9, #252]	; 0xfc
	add	r0, r9, #244	; 0xf4
	bl	OS_WakeupThread
	ldr	r0, [r9, #252]	; 0xfc
	ands	r0, r0, #16
	beq	_03800D08
	mov	r0, r5
	bl	OS_WakeupThreadDirect
_03800D08:
	mov	r0, sl
	bl	OS_RestoreInterrupts
	b	_03800B44
_03800D14:
	mov	r0, r9
	ldr	r1, [r9, #68]	; 0x44
	mov	lr, pc
	bx	r1
	b	_03800B44
_03800D28:	.word	cardi_common
