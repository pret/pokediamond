	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _0380912C
_0380912C: ;0x0380912C
	.space 0x03809140 - 0x0380912C

	.global cardi_common
cardi_common: ;0x03809140
	.space 0x03809188 - 0x03809140

	.global _03809188
_03809188: ;0x03809188
	.space 0x03809760 - 0x03809188

	.global _03809760
_03809760: ;0x03809760
	.space 0x03809764 - 0x03809760

    .section .text

	arm_func_start CARD_GetRomHeader
CARD_GetRomHeader: ; 0x037FFF20
	ldr	r0, _037FFF28	; =0x027FFA80
	bx	lr
_037FFF28:	.word	0x027FFA80

	arm_func_start CARD_SetThreadPriority
CARD_SetThreadPriority: ; 0x037FFF2C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	ldr	r6, _037FFF70	; =cardi_common
	bl	OS_DisableInterrupts
	mov	r4, r0
	ldr	r5, [r6, #240]	; 0xf0
	str	r7, [r6, #240]	; 0xf0
	add	r0, r6, #72	; 0x48
	ldr	r1, [r6, #240]	; 0xf0
	bl	OS_SetThreadPriority
	mov	r0, r4
	bl	OS_RestoreInterrupts
	mov	r0, r5
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FFF70:	.word	cardi_common

	arm_func_start CARD_Enable
CARD_Enable: ; 0x037FFF74
	ldr	r1, _037FFF80	; =_0380912C
	str	r0, [r1]
	bx	lr
_037FFF80:	.word	_0380912C

	arm_func_start CARDi_InitCommon
CARDi_InitCommon: ; 0x037FFF84
	stmfd	sp!, {lr}
	sub	sp, sp, #12
	mvn	r1, #2
	ldr	r0, _0380001C	; =cardi_common
	str	r1, [r0, #12]
	mov	r2, #0
	str	r2, [r0, #16]
	str	r2, [r0, #28]
	str	r2, [r0]
	str	r2, [r0, #8]
	str	r2, [r0, #24]
	str	r2, [r0, #20]
	str	r2, [r0, #248]	; 0xf8
	str	r2, [r0, #244]	; 0xf4
	mov	r1, #4
	str	r1, [r0, #240]	; 0xf0
	mov	r1, #1024	; 0x400
	str	r1, [sp]
	ldr	r0, [r0, #240]	; 0xf0
	str	r0, [sp, #4]
	ldr	r0, _03800020	; =_03809188
	ldr	r1, _03800024	; =CARDi_TaskThread
	ldr	r3, _03800028	; =_03809760
	bl	OS_CreateThread
	ldr	r0, _03800020	; =_03809188
	bl	OS_WakeupThreadDirect
	mov	r0, #11
	ldr	r1, _0380002C	; =CARDi_OnFifoRecv
	bl	PXI_SetFifoRecvCallback
	ldr	r0, _03800030	; =0x027FFC40
	ldrh	r0, [r0]
_03800000:
	cmp	r0, #2
	beq	_03800010
	mov	r0, #1
	bl	CARD_Enable
_03800010:
	add	sp, sp, #12
	ldmia	sp!, {lr}
	bx	lr
_0380001C:	.word	cardi_common
_03800020:	.word	_03809188
_03800024:	.word	CARDi_TaskThread
_03800028:	.word	_03809760
_0380002C:	.word	CARDi_OnFifoRecv
_03800030:	.word	0x027FFC40
