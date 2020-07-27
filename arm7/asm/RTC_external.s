	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global _0380A210
_0380A210: ;0x0380A210
	.space 0x0380A3F0 - 0x0380A210

	.section .text

	arm_func_start RTC_Init
RTC_Init: ;@ 0x03805954
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #8
	mov	r4, r0
	ldr	r0, _03805A28	;@ =_0380A038
	ldrh	r1, [r0]
	cmp	r1, #0
	bne	_03805A1C
	mov	r1, #1
	strh	r1, [r0]
	ldr	r0, _03805A2C	;@ =_0380A03C
	str	r1, [r0, #468]	;@ 0x1d4
	bl	FUN_03805158
	mov	r1, #0
	ldr	r0, _03805A2C	;@ =_0380A03C
	str	r1, [r0, #468]	;@ 0x1d4
	bl	PXI_Init
	mov	r0, #5
	ldr	r1, _03805A30	;@ =FUN_03805818
	bl	PXI_SetFifoRecvCallback
	ldr	r0, _03805A2C	;@ =_0380A03C
	ldr	r1, _03805A34	;@ =_0380A05C
	mov	r2, #4
	bl	OS_InitMessageQueue
	mov	r0, #256	;@ 0x100
	str	r0, [sp]
	str	r4, [sp, #4]
	ldr	r0, _03805A38	;@ =_0380A06C
	ldr	r1, _03805A3C	;@ =FUN_0380531C
	mov	r2, #0
	ldr	r3, _03805A40	;@ =_0380A210
	bl	OS_CreateThread
	ldr	r0, _03805A38	;@ =_0380A06C
	bl	OS_WakeupThreadDirect
	mov	r0, #32768	;@ 0x8000
	bl	EXIi_SelectRcnt
	mov	r0, #64	;@ 0x40
	mov	r1, #0
	bl	EXIi_SetBitRcnt0L
	mov	r0, #256	;@ 0x100
	mov	r1, r0
	bl	EXIi_SetBitRcnt0L
	bl	OS_DisableInterrupts
	mov	r4, r0
	mov	r0, #128	;@ 0x80
	ldr	r1, _03805A44	;@ =FUN_0380528C
	bl	OS_SetIrqFunction
	mov	r0, #128	;@ 0x80
	bl	OS_EnableIrqMask
	mov	r0, r4
	bl	OS_RestoreInterrupts
_03805A1C:
	add	sp, sp, #8
	ldmia	sp!, {r4, lr}
	bx	lr
_03805A28:	.word	_0380A038
_03805A2C:	.word	_0380A03C
_03805A30:	.word	FUN_03805818
_03805A34:	.word	_0380A05C
_03805A38:	.word	_0380A06C
_03805A3C:	.word	FUN_0380531C
_03805A40:	.word	_0380A210
_03805A44:	.word	FUN_0380528C
